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
include test/CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/client.dir/flags.make

test/CMakeFiles/client.dir/client.cc.o: test/CMakeFiles/client.dir/flags.make
test/CMakeFiles/client.dir/client.cc.o: ../test/client.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/workstation/lockstep/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/client.dir/client.cc.o"
	cd /mnt/hgfs/workstation/lockstep/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/client.cc.o -c /mnt/hgfs/workstation/lockstep/test/client.cc

test/CMakeFiles/client.dir/client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client.cc.i"
	cd /mnt/hgfs/workstation/lockstep/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/workstation/lockstep/test/client.cc > CMakeFiles/client.dir/client.cc.i

test/CMakeFiles/client.dir/client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client.cc.s"
	cd /mnt/hgfs/workstation/lockstep/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/workstation/lockstep/test/client.cc -o CMakeFiles/client.dir/client.cc.s

test/CMakeFiles/client.dir/client.cc.o.requires:

.PHONY : test/CMakeFiles/client.dir/client.cc.o.requires

test/CMakeFiles/client.dir/client.cc.o.provides: test/CMakeFiles/client.dir/client.cc.o.requires
	$(MAKE) -f test/CMakeFiles/client.dir/build.make test/CMakeFiles/client.dir/client.cc.o.provides.build
.PHONY : test/CMakeFiles/client.dir/client.cc.o.provides

test/CMakeFiles/client.dir/client.cc.o.provides.build: test/CMakeFiles/client.dir/client.cc.o


test/CMakeFiles/client.dir/game.pb.cc.o: test/CMakeFiles/client.dir/flags.make
test/CMakeFiles/client.dir/game.pb.cc.o: ../test/game.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/workstation/lockstep/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/client.dir/game.pb.cc.o"
	cd /mnt/hgfs/workstation/lockstep/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/game.pb.cc.o -c /mnt/hgfs/workstation/lockstep/test/game.pb.cc

test/CMakeFiles/client.dir/game.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/game.pb.cc.i"
	cd /mnt/hgfs/workstation/lockstep/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/workstation/lockstep/test/game.pb.cc > CMakeFiles/client.dir/game.pb.cc.i

test/CMakeFiles/client.dir/game.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/game.pb.cc.s"
	cd /mnt/hgfs/workstation/lockstep/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/workstation/lockstep/test/game.pb.cc -o CMakeFiles/client.dir/game.pb.cc.s

test/CMakeFiles/client.dir/game.pb.cc.o.requires:

.PHONY : test/CMakeFiles/client.dir/game.pb.cc.o.requires

test/CMakeFiles/client.dir/game.pb.cc.o.provides: test/CMakeFiles/client.dir/game.pb.cc.o.requires
	$(MAKE) -f test/CMakeFiles/client.dir/build.make test/CMakeFiles/client.dir/game.pb.cc.o.provides.build
.PHONY : test/CMakeFiles/client.dir/game.pb.cc.o.provides

test/CMakeFiles/client.dir/game.pb.cc.o.provides.build: test/CMakeFiles/client.dir/game.pb.cc.o


# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/client.cc.o" \
"CMakeFiles/client.dir/game.pb.cc.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

../bin/client: test/CMakeFiles/client.dir/client.cc.o
../bin/client: test/CMakeFiles/client.dir/game.pb.cc.o
../bin/client: test/CMakeFiles/client.dir/build.make
../bin/client: test/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/workstation/lockstep/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../bin/client"
	cd /mnt/hgfs/workstation/lockstep/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/client.dir/build: ../bin/client

.PHONY : test/CMakeFiles/client.dir/build

test/CMakeFiles/client.dir/requires: test/CMakeFiles/client.dir/client.cc.o.requires
test/CMakeFiles/client.dir/requires: test/CMakeFiles/client.dir/game.pb.cc.o.requires

.PHONY : test/CMakeFiles/client.dir/requires

test/CMakeFiles/client.dir/clean:
	cd /mnt/hgfs/workstation/lockstep/build/test && $(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/client.dir/clean

test/CMakeFiles/client.dir/depend:
	cd /mnt/hgfs/workstation/lockstep/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/workstation/lockstep /mnt/hgfs/workstation/lockstep/test /mnt/hgfs/workstation/lockstep/build /mnt/hgfs/workstation/lockstep/build/test /mnt/hgfs/workstation/lockstep/build/test/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/client.dir/depend

