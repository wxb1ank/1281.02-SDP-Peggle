# ~The Peggle Makefile~
# Author: Will Blankemeyer

# Note: I have only tested this on Windows so it may fail on *nix-based platforms.
#
# Note: For brevity, "simulator" is shorthand for "FEH Proteus simulator", and "simulator repo" is
#       shorthand for "simulator Git repository".
#
# Note: The Makefile language is a Turing tarpit. Among other shortcomings, it lacks an obvious type
#       system. For the convenience of the reader, all variables have been annotated with a
#       *quot*[1] `::` followed by a tag that categorizes the information contained within. The full
#       list of variable tags used in this Makefile is given below:
#		  - text
#				A generic string that does not contain whitespace.
#   	  - rel-path
#				A type of `text` that represents a filesystem path relative to the current
#				directory.
#   	  - exe
#				A type of `text` that represents the name of an executable program accessible from a
#				shell.
#  	      - A -> B
#				A Makefile function that receives an argument of type `A` and returns type `B`.
#         - [A]
#				A list of type `A`.
#
# [1]: I think Jake came up with the name. In this context, `::` is read *has type*. I stole this
#      interpretation from Haskell.

# :: text
# The name of the simulator repo.
REPO_NAME := simulator_libraries
# :: text
# The URL to the simulator repo.
REPO_URL := https://code.osu.edu/fehelectronics/proteus_software/$(REPO_NAME).git
# :: text
# The short commit hash of the vendored simulator repo.
#
# Once the simulator repo is cloned locally, this commit hash is checked-out.
REPO_HASH := c1a1b28

# :: rel-path
# The relative path to the local simulator repo directory.
REPO_DIR := Vendor/$(REPO_NAME)
# :: rel-path
# The relative path to the directory in which object files and generated documentation are stored.
BUILD_DIR := Build
# :: rel-path
# The relative path to the directory containing OS-specicfic shell scripts.
#
# This directory currently contains the `clone-deps` script, which is executed in the recipe of the
# same name.
SCRIPTS_DIR := Scripts

# :: exe
# The name of the system Git executable.
GIT := git
# :: exe
# The name of the system C++ compiler.
CXX := g++
# :: exe
# The name of the system C compiler.
CC := gcc
# :: exe
# The name of the system Doxygen executable.
DOXYGEN := doxygen

# Note: it is important that these variables are assigned with `=` rather than `:=` because their
# values may change over the course of the Makefile. Notably, if dependencies need to be pulled,
# then the source tree will be modified, which affects the value of `$(SRC_DIRS)` and, by extension,
# nearly everything else.

# :: rel-path -> [rel-path]
# Returns a list of relative paths to all nested subdirectories of the given directory, *excluding*
# the given directory itself.
#
# This function is an implementation detail of `recurse_dirs`, which should be used instead.
_recurse_dirs = $(foreach dir,$(dir $(wildcard $1*/.)),$(dir) $(call _recurse_dirs,$(dir)))
# :: rel-path -> [rel-path]
# Returns a list of relative paths to the given directory and all nested subdirectories therein.
#
# Each returned path is prefixed with the path of the given directory. For example, if the given
# directory is `./`, then every path will begin with `./`.
#
# Unlike `_recurse_dirs`, the returned list includes the given directory itself.
recurse_dirs = $1 $(call _recurse_dirs,$1)
# :: [rel-path]
# The list of relative paths to all directories that *may* contain Peggle or simulator source files.
#
# This function simply returns paths to all directories that aren't the build directory.
SRC_DIRS = $(filter-out ./$(BUILD_DIR)/%,$(call recurse_dirs,./))
# :: [rel-path]
# The list of relative paths to all Peggle and simulator source files.
SRCS = $(patsubst ./%,%,$(foreach suffix,.cpp .c,$(wildcard $(addsuffix *$(suffix),$(SRC_DIRS)))))

# :: text -> [rel-path]
# Returns a list of relative paths to all Peggle and simulator object files compiled from source
# files with names ending with the given suffix.
filter_objs = $(addprefix $(BUILD_DIR)/,$(patsubst %$1,%.o,$(filter %$1,$(SRCS))))
# :: [rel-path]
# The list of relative paths to all Peggle and simulator object files compiled from C++ source
# files.
CXX_OBJS = $(call filter_objs,.cpp)
# :: [rel-path]
# The list of relative paths to all Peggle and simulator object files compiled from C source files.
C_OBJS = $(call filter_objs,.c)
# :: [rel-path]
# The list of relative paths to all Peggle and simulator object files.
OBJS = $(CXX_OBJS) $(C_OBJS)

# :: [rel-path]
# The list of relative paths to all Peggle and simulator dependency Makefiles generated from C++
# source files.
CXX_DEPS = $(CXX_OBJS:.o=.d)
# :: [rel-path]
# The list of relative paths to all Peggle and simulator dependency Makefiles generated from C
# source files.
C_DEPS = $(C_OBJS:.o=.d)
# :: [rel-path]
# The list of relative paths to all Peggle and simulator dependency Makefiles.
DEPS = $(CXX_DEPS) $(C_DEPS)

# :: [rel-path]
# The list of relative paths to directories containing C/C++ header files that should be marked as
# include directories with the GCC `-I` option.
INC_DIRS := $(REPO_DIR) Headers
# :: [text]
# The list of GCC `-I` arguments that should be passed to all compiler invocations.
INCFLAGS := $(foreach dir,$(INC_DIRS),-I$(dir))
# :: [text]
# The list of GCC `-W` arguments that should be passed to all compiler invocations.
WARNFLAGS := $(foreach name,all extra pedantic conversion float-equal,-W$(name))
# :: text
# The revision of the C++ standard to compile C++ source files with.
CXX_STD := 17
# :: text
# The revision of the C standard to compile C source files with.
C_STD := 17

# :: [text]
# The list of arguments that should be passed to all compiler invocations.
COMMON_FLAGS := $(INCFLAGS) $(WARNFLAGS) -Os -MMD -MP

# :: [text]
# A shell command 'epilogue' that causes the output of the preceding command to be discarded.
ifeq ($(OS),Windows_NT)
	SUPPRESS_SHELL := > nul 2>&1
else
	SUPPRESS_SHELL := 2> /dev/null
endif
# :: exe -> exe
# Returns a suppressed version of the given shell command that discards standard output and error.
quiet_shell = $1 $(SUPPRESS_SHELL)

# OPEN :: exe
# The name of the system `open` executable that opens a file with its default handler program.
#
# mkdir :: rel-path -> exe
# Returns a shell command that creates the given directory.
#
# rm :: rel-path -> exe
# Returns a shell command that removes the given file.
#
# rmdir :: rel-path -> exe
# Returns a shell command that removes the given directory, including all contained files and nested
# subdirectories.
#
# LDFLAGS :: [text]
# The list of arguments that should be passed to all linker invocations.
#
# TARGET_SUFFIX :: text
# The file exension of the target executable. On Windows, this is `.exe`; on other platforms, this
# is empty.
ifeq ($(OS),Windows_NT)
# :: exe
# The name of the command prompt program.
	SHELL := cmd
	OPEN := start ""

# :: rel-path -> rel-path
# Replaces all occurences of `/` with `\` in the given filesystem path.
	flip_slashes = $(subst /,\,$1)

	mkdir = $(call quiet_shell,md $(call flip_slashes,$1))
	rm = $(call quiet_shell,del /q $(call flip_slashes,$1))
	rmdir = $(call quiet_shell,rd /s /q $(call flip_slashes,$1))

	LDFLAGS := -lopengl32 -lgdi32

	TARGET_SUFFIX := .exe
else
	mkdir = $(call quiet_shell,mkdir -p $1)
	rm = $(call quiet_shell,rm -f $1)
# The 'frfr' is essential for this to work.
	rmdir = $(call quiet_shell,rm -frfr $1)

	ifeq ($(shell uname),Darwin)
		OPEN := open

		LDFLAGS := -framework OpenGL -framework Cocoa
		COMMON_FLAGS := $(COMMON_FLAGS) -DOBJC_OLD_DISPATCH_PROTOTYPES
	else
		OPEN := xdg-open

		LDFLAGS := `pkg-config --libs --cflags opengl x11 glx`
	endif

	TARGET_SUFFIX :=
endif

# rel-path
# The relative path to the target executable.
TARGET := game$(TARGET_SUFFIX)

# :: [text]
# The list of arguments that should be passed to all C++ compiler invocations.
CXXFLAGS := $(COMMON_FLAGS) -std=c++$(CXX_STD)
# :: [text]
# The list of arguments that should be passed to all C compiler invocations.
CFLAGS := $(COMMON_FLAGS) -std=c$(C_STD)

.PHONY: checkout-deps clone-deps doc docs open-doc open-docs clean
# This allows us to omit the `@` before shell commands in recipes.
.SILENT:

# Builds the target executable, pulling dependencies if necessary.
all: checkout-deps $(TARGET)

# Checks-out vendored repositories to the correct commit hash.
checkout-deps: clone-deps
	@$(GIT) -C $(REPO_DIR) config advice.detachedHead false
	@$(GIT) -C $(REPO_DIR) checkout $(REPO_HASH)

# Clones all dependency repositories.
clone-deps:
ifeq ($(OS),Windows_NT)
	$(SCRIPTS_DIR)\clone-deps.bat $(GIT) $(REPO_DIR) $(REPO_URL)
else
	./$(SCRIPTS_DIR)/clone-deps.sh $(GIT) $(REPO_DIR) $(REPO_URL)
endif

# Links the target executable.
$(TARGET): $(OBJS)
	echo [LD ] $@
	$(CXX) -o $@ $^ $(LDFLAGS)

.SECONDEXPANSION:

# Compiles all C++ source files.
$(CXX_OBJS): $(BUILD_DIR)/%.o: %.cpp | $$(@D)/.
	echo [CXX] $@
	$(CXX) -o $@ -c $< $(CXXFLAGS)

# Compiles all C source files.
$(C_OBJS): $(BUILD_DIR)/%.o: %.c | $$(@D)/.
	echo [CC ] $@
	$(CC) -o $@ -c $< $(CFLAGS)

# Creates the build directory.
$(BUILD_DIR)/.:
	$(call mkdir,$(dir $@))
# Creates all subdirectories of the build directory.
$(BUILD_DIR)/%/.:
	$(call mkdir,$(dir $@))

-include $(DEPS)

# Generates the Peggle documentation with Doxygen.
#
# The generated webpage files are written to the build directory.
doc docs:
	$(DOXYGEN)

# Opens the generated Peggle documentation in the system browser.
open-doc open-docs:
	$(OPEN) $(BUILD_DIR)/html/index.html

# Deletes the target executable and build directory.
clean:
	-$(call rm,$(TARGET))
	-$(call rmdir,$(BUILD_DIR))
