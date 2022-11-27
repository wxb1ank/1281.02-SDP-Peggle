# ~The Peggle Makefile~
# Author: Will Blankemeyer
#
# Note: I have only tested this on Windows so it may fail on *nix-based platforms.

# TODO: Object files should depend on headers, if they exist.

REPO_NAME := simulator_libraries
REPO_URL := https://code.osu.edu/fehelectronics/proteus_software/$(REPO_NAME).git
REPO_HASH := c1a1b28

REPO_DIR := $(REPO_NAME)
BUILD_DIR := build

GIT := git
CXX := g++
CC := gcc
DOXYGEN := doxygen

_recurse_dirs = $(foreach dir,$(dir $(wildcard $1*/.)),$(dir) $(call _recurse_dirs,$(dir)))
recurse_dirs = $1 $(call _recurse_dirs,$1)
SRC_DIRS := $(filter-out ./$(BUILD_DIR)/%,$(call recurse_dirs,./))
SRCS := $(patsubst ./%,%,$(foreach suffix,.cpp .c,$(wildcard $(addsuffix *$(suffix),$(SRC_DIRS)))))

OBJ_DIRS := $(subst /./,/,$(addprefix $(BUILD_DIR)/,$(SRC_DIRS)))
filter_objs = $(addprefix $(BUILD_DIR)/,$(patsubst %$1,%.o,$(filter %$1,$(SRCS))))
CXX_OBJS := $(call filter_objs,.cpp)
CC_OBJS := $(call filter_objs,.c)
OBJS := $(CXX_OBJS) $(CC_OBJS)

INC_DIRS := $(REPO_DIR)
INCFLAGS := $(foreach dir,$(INC_DIRS),-I$(dir))
CXX_STD := 17
CC_STD := 17

COMMON_FLAGS := $(INCFLAGS) -Os -MMD -MP -w

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
CFLAGS := $(COMMON_FLAGS) -std=c$(CC_STD)

.PHONY: checkout clone doc docs open-doc open-docs clean

all: checkout $(TARGET)

checkout:
	@$(GIT) -C $(REPO_DIR) checkout $(REPO_HASH)

clone:
ifeq ($(OS),Windows_NT)
# check for internet connection
# if there's internet, check to see if Libraries folder exists
# if it does, remove it before cloning the repo
	@ping -n 1 -w 1000 $(REPO_URL) > NUL & \
	if errorlevel 1 \
	( \
		( echo Warning: No internet connection! ) \
	) \
	else \
	( \
		( if exist "$(REPO_DIR)" \
		( \
			cd $(REPO_DIR) && \
			$(GIT) stash && \
			$(GIT) pull && \
			cd .. \
		) \
		else \
		( \
			$(GIT) clone $(REPO_URL) \
		) \
		) \
	)
else
# Mac/Linux
	@ping -c 1 -W 1000 $(REPO_URL) > /dev/null ; \
	if [ "$$?" -ne 0 ]; then \
		echo Warning: No internet connection!; \
	else \
		if [ -d "$(REPO_DIR)" ]; then \
			cd $(REPO_DIR) ; \
			$(GIT) stash ; \
      		$(GIT) pull ; \
      		cd .. ; \
		else \
      		$(GIT) clone $(REPO_URL) ; \
		fi \
	fi
endif

$(TARGET): $(OBJS)
	@echo [LD ] $@
	@$(CXX) -o $@ $^ $(LDFLAGS)

$(CXX_OBJS): $(BUILD_DIR)/%.o: %.cpp | $(OBJ_DIRS)
	@echo [CXX] $@
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

$(CC_OBJS): $(BUILD_DIR)/%.o: %.c | $(OBJ_DIRS)
	@echo [CC ] $@
	@$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ_DIRS):
	@-$(call mkdir,$(dir $@))

doc docs:
	@$(DOXYGEN)

open-doc open-docs:
	@$(OPEN) $(BUILD_DIR)/html/index.html

clean:
	@-$(call rm,$(TARGET))
	@-$(call rmdir,$(BUILD_DIR))
