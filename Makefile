# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.16.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.16.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/leon/CLionProjects/shelly

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/leon/CLionProjects/shelly

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.16.3/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.16.3/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/leon/CLionProjects/shelly/CMakeFiles /Users/leon/CLionProjects/shelly/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/leon/CLionProjects/shelly/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named shelly

# Build rule for target.
shelly: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 shelly
.PHONY : shelly

# fast build rule for target.
shelly/fast:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/build
.PHONY : shelly/fast

input.o: input.c.o

.PHONY : input.o

# target to build an object file
input.c.o:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/input.c.o
.PHONY : input.c.o

input.i: input.c.i

.PHONY : input.i

# target to preprocess a source file
input.c.i:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/input.c.i
.PHONY : input.c.i

input.s: input.c.s

.PHONY : input.s

# target to generate assembly for a file
input.c.s:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/input.c.s
.PHONY : input.c.s

main.o: main.c.o

.PHONY : main.o

# target to build an object file
main.c.o:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/main.c.o
.PHONY : main.c.o

main.i: main.c.i

.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s

.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/main.c.s
.PHONY : main.c.s

parse.o: parse.c.o

.PHONY : parse.o

# target to build an object file
parse.c.o:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/parse.c.o
.PHONY : parse.c.o

parse.i: parse.c.i

.PHONY : parse.i

# target to preprocess a source file
parse.c.i:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/parse.c.i
.PHONY : parse.c.i

parse.s: parse.c.s

.PHONY : parse.s

# target to generate assembly for a file
parse.c.s:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/parse.c.s
.PHONY : parse.c.s

process.o: process.c.o

.PHONY : process.o

# target to build an object file
process.c.o:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/process.c.o
.PHONY : process.c.o

process.i: process.c.i

.PHONY : process.i

# target to preprocess a source file
process.c.i:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/process.c.i
.PHONY : process.c.i

process.s: process.c.s

.PHONY : process.s

# target to generate assembly for a file
process.c.s:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/process.c.s
.PHONY : process.c.s

utils.o: utils.c.o

.PHONY : utils.o

# target to build an object file
utils.c.o:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/utils.c.o
.PHONY : utils.c.o

utils.i: utils.c.i

.PHONY : utils.i

# target to preprocess a source file
utils.c.i:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/utils.c.i
.PHONY : utils.c.i

utils.s: utils.c.s

.PHONY : utils.s

# target to generate assembly for a file
utils.c.s:
	$(MAKE) -f CMakeFiles/shelly.dir/build.make CMakeFiles/shelly.dir/utils.c.s
.PHONY : utils.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... shelly"
	@echo "... input.o"
	@echo "... input.i"
	@echo "... input.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... parse.o"
	@echo "... parse.i"
	@echo "... parse.s"
	@echo "... process.o"
	@echo "... process.i"
	@echo "... process.s"
	@echo "... utils.o"
	@echo "... utils.i"
	@echo "... utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

