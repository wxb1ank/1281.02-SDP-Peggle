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
# The short commit hash of the specific version of the simulator repo that Peggle depends upon.
#
# Once the simulator repo is cloned locally, this commit hash is checked-out.
REPO_HASH := c1a1b28

# :: rel-path
# The relative path to the local simulator repo directory.
REPO_DIR := $(REPO_NAME)
# :: rel-path
# The relative path to the directory to which object files and generated documentation are written.
BUILD_DIR := Build
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

# :: rel-path -> [rel-path]
# Returns a list of relative paths to all nested subdirectories of the given directory.
_recurse_dirs = $(foreach dir,$(dir $(wildcard $1*/.)),$(dir) $(call _recurse_dirs,$(dir)))
# :: rel-path -> [rel-path]
# Returns a list of relative paths to the given directory and all nested subdirectories therein.
recurse_dirs = $1 $(call _recurse_dirs,$1)
# :: [rel-path]
# The list of relative paths to all directories that *may* contain Peggle or simulator source files.
SRC_DIRS := $(filter-out ./$(BUILD_DIR)/%,$(call recurse_dirs,./))
# :: [rel-path]
# The list of relative paths to all Peggle and simulator source files.
SRCS := $(patsubst ./%,%,$(foreach suffix,.cpp .c,$(wildcard $(addsuffix *$(suffix),$(SRC_DIRS)))))

# :: [rel-path]
# The list of relative paths to all subdirectories in the build directory that *may* contain Peggle
# or simulator object files.
OBJ_DIRS := $(subst /./,/,$(addprefix $(BUILD_DIR)/,$(SRC_DIRS)))
# :: text -> [rel-path]
# Returns a list of relative paths to all Peggle and simulator object files compiled from source
# files with names ending with the given suffix.
filter_objs = $(addprefix $(BUILD_DIR)/,$(patsubst %$1,%.o,$(filter %$1,$(SRCS))))
# :: [rel-path]
# The list of relative paths to all Peggle and simulator object files compiled from C++ source
# files.
CXX_OBJS := $(call filter_objs,.cpp)
# :: [rel-path]
# The list of relative paths to all Peggle and simulator object files compiled from C source files.
C_OBJS := $(call filter_objs,.c)
# :: [rel-path]
# The list of relative paths to all Peggle and simulator object files.
OBJS := $(CXX_OBJS) $(C_OBJS)

# :: [rel-path]
# The list of relative paths to all Peggle and simulator dependency Makefiles generated from C++
# source files.
CXX_DEPS := $(CXX_OBJS:.o=.d)
# :: [rel-path]
# The list of relative paths to all Peggle and simulator dependency Makefiles generated from C
# source files.
C_DEPS := $(C_OBJS:.o=.d)
# :: [rel-path]
# The list of relative paths to all Peggle and simulator dependency Makefiles.
DEPS := $(CXX_DEPS) $(C_DEPS)

INC_DIRS := $(REPO_DIR) Headers
INCFLAGS := $(foreach dir,$(INC_DIRS),-I$(dir))
CXX_STD := 17
C_STD := 17

COMMON_FLAGS := $(INCFLAGS) -Os -w -MMD -MP

ifeq ($(OS),Windows_NT)
	SUPPRESS_SHELL := > nul 2>&1
else
	SUPPRESS_SHELL := 2> /dev/null
endif
quiet_shell = $1 $(SUPPRESS_SHELL)

ifeq ($(OS),Windows_NT)
	SHELL := CMD
	OPEN := start ""

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

TARGET := game$(TARGET_SUFFIX)

CXXFLAGS := $(COMMON_FLAGS) -std=c++$(CXX_STD)
CFLAGS := $(COMMON_FLAGS) -std=c$(C_STD)

.PHONY: checkout-deps clone-deps doc docs open-doc open-docs clean
.SILENT:

all: checkout-deps $(TARGET)

checkout-deps: clone-deps
	@$(GIT) -C $(REPO_DIR) checkout $(REPO_HASH)

clone-deps:
ifeq ($(OS),Windows_NT)
	$(SCRIPTS_DIR)\clone-deps.bat $(GIT) $(REPO_DIR) $(REPO_URL)
else
	./$(SCRIPTS_DIR)/clone-deps.sh $(GIT) $(REPO_DIR) $(REPO_URL)
endif

$(TARGET): $(OBJS)
	echo [LD ] $@
	$(CXX) -o $@ $^ $(LDFLAGS)

.SECONDEXPANSION:

$(CXX_OBJS): $(BUILD_DIR)/%.o: %.cpp | $$(@D)/.
	echo [CXX] $@
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(C_OBJS): $(BUILD_DIR)/%.o: %.c | $$(@D)/.
	echo [CC ] $@
	$(CC) -o $@ -c $< $(CFLAGS)

$(BUILD_DIR)/.:
	$(call mkdir,$(dir $@))
$(BUILD_DIR)/%/.:
	$(call mkdir,$(dir $@))

-include $(DEPS)

# Generates the Peggle documentation with Doxygen.
#
# The generated webpage files are written to the build directory.
doc docs:
	$(DOXYGEN)

open-doc open-docs:
	$(OPEN) $(BUILD_DIR)/html/index.html

# Deletes the target executable and build directory.
clean:
	-$(call rm,$(TARGET))
	-$(call rmdir,$(BUILD_DIR))
