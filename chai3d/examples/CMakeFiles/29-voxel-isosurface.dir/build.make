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
include CMakeFiles/29-voxel-isosurface.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/29-voxel-isosurface.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/29-voxel-isosurface.dir/flags.make

CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o: CMakeFiles/29-voxel-isosurface.dir/flags.make
CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o: GLFW/29-voxel-isosurface/29-voxel-isosurface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/29-voxel-isosurface/29-voxel-isosurface.cpp

CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/29-voxel-isosurface/29-voxel-isosurface.cpp > CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.i

CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/29-voxel-isosurface/29-voxel-isosurface.cpp -o CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.s

CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o.requires:

.PHONY : CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o.requires

CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o.provides: CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o.requires
	$(MAKE) -f CMakeFiles/29-voxel-isosurface.dir/build.make CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o.provides.build
.PHONY : CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o.provides

CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o.provides.build: CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o


# Object files for target 29-voxel-isosurface
29__voxel__isosurface_OBJECTS = \
"CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o"

# External object files for target 29-voxel-isosurface
29__voxel__isosurface_EXTERNAL_OBJECTS =

29-voxel-isosurface: CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o
29-voxel-isosurface: CMakeFiles/29-voxel-isosurface.dir/build.make
29-voxel-isosurface: CMakeFiles/29-voxel-isosurface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 29-voxel-isosurface"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/29-voxel-isosurface.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/29-voxel-isosurface.dir/build: 29-voxel-isosurface

.PHONY : CMakeFiles/29-voxel-isosurface.dir/build

CMakeFiles/29-voxel-isosurface.dir/requires: CMakeFiles/29-voxel-isosurface.dir/29-voxel-isosurface/29-voxel-isosurface.o.requires

.PHONY : CMakeFiles/29-voxel-isosurface.dir/requires

CMakeFiles/29-voxel-isosurface.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/29-voxel-isosurface.dir/cmake_clean.cmake
.PHONY : CMakeFiles/29-voxel-isosurface.dir/clean

CMakeFiles/29-voxel-isosurface.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles/29-voxel-isosurface.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/29-voxel-isosurface.dir/depend

