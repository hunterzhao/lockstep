# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/hgfs/workstation/lockstep

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/workstation/lockstep/build

# Include any dependencies generated for this target.
include test/CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/server.dir/flags.make

test/CMakeFiles/server.dir/server.cc.o: test/CMakeFiles/server.dir/flags.make
test/CMakeFiles/server.dir/server.cc.o: ../test/server.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/workstation/lockstep/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/server.dir/server.cc.o"
	cd /mnt/hgfs/workstation/lockstep/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server.cc.o -c /mnt/hgfs/workstation/lockstep/test/server.cc

test/CMakeFiles/server.dir/server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server.cc.i"
	cd /mnt/hgfs/workstation/lockstep/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/workstation/lockstep/test/server.cc > CMakeFiles/server.dir/server.cc.i

test/CMakeFiles/server.dir/server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server.cc.s"
	cd /mnt/hgfs/workstation/lockstep/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/workstation/lockstep/test/server.cc -o CMakeFiles/server.dir/server.cc.s

test/CMakeFiles/server.dir/server.cc.o.requires:

.PHONY : test/CMakeFiles/server.dir/server.cc.o.requires

test/CMakeFiles/server.dir/server.cc.o.provides: test/CMakeFiles/server.dir/server.cc.o.requires
	$(MAKE) -f test/CMakeFiles/server.dir/build.make test/CMakeFiles/server.dir/server.cc.o.provides.build
.PHONY : test/CMakeFiles/server.dir/server.cc.o.provides

test/CMakeFiles/server.dir/server.cc.o.provides.build: test/CMakeFiles/server.dir/server.cc.o


# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/server.cc.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

../bin/server: test/CMakeFiles/server.dir/server.cc.o
../bin/server: test/CMakeFiles/server.dir/build.make
../bin/server: src/libgame.a
../bin/server: test/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/workstation/lockstep/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/server"
	cd /mnt/hgfs/workstation/lockstep/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/server.dir/build: ../bin/server

.PHONY : test/CMakeFiles/server.dir/build

test/CMakeFiles/server.dir/requires: test/CMakeFiles/server.dir/server.cc.o.requires

.PHONY : test/CMakeFiles/server.dir/requires

test/CMakeFiles/server.dir/clean:
	cd /mnt/hgfs/workstation/lockstep/build/test && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/server.dir/clean

test/CMakeFiles/server.dir/depend:
	cd /mnt/hgfs/workstation/lockstep/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/workstation/lockstep /mnt/hgfs/workstation/lockstep/test /mnt/hgfs/workstation/lockstep/build /mnt/hgfs/workstation/lockstep/build/test /mnt/hgfs/workstation/lockstep/build/test/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/server.dir/depend

