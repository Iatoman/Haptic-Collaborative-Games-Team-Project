# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cs_group_2021_21/Desktop/chai3d/examples

# Include any dependencies generated for this target.
include CMakeFiles/28-voxel-basic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/28-voxel-basic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/28-voxel-basic.dir/flags.make

CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o: CMakeFiles/28-voxel-basic.dir/flags.make
CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o: GLFW/28-voxel-basic/28-voxel-basic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/28-voxel-basic/28-voxel-basic.cpp

CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/28-voxel-basic/28-voxel-basic.cpp > CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.i

CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/28-voxel-basic/28-voxel-basic.cpp -o CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.s

CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o.requires:

.PHONY : CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o.requires

CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o.provides: CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o.requires
	$(MAKE) -f CMakeFiles/28-voxel-basic.dir/build.make CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o.provides.build
.PHONY : CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o.provides

CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o.provides.build: CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o


# Object files for target 28-voxel-basic
28__voxel__basic_OBJECTS = \
"CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o"

# External object files for target 28-voxel-basic
28__voxel__basic_EXTERNAL_OBJECTS =

28-voxel-basic: CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o
28-voxel-basic: CMakeFiles/28-voxel-basic.dir/build.make
28-voxel-basic: CMakeFiles/28-voxel-basic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 28-voxel-basic"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/28-voxel-basic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/28-voxel-basic.dir/build: 28-voxel-basic

.PHONY : CMakeFiles/28-voxel-basic.dir/build

CMakeFiles/28-voxel-basic.dir/requires: CMakeFiles/28-voxel-basic.dir/28-voxel-basic/28-voxel-basic.o.requires

.PHONY : CMakeFiles/28-voxel-basic.dir/requires

CMakeFiles/28-voxel-basic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/28-voxel-basic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/28-voxel-basic.dir/clean

CMakeFiles/28-voxel-basic.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles/28-voxel-basic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/28-voxel-basic.dir/depend
