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
include CMakeFiles/20-map.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/20-map.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/20-map.dir/flags.make

CMakeFiles/20-map.dir/20-map/20-map.o: CMakeFiles/20-map.dir/flags.make
CMakeFiles/20-map.dir/20-map/20-map.o: GLFW/20-map/20-map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/20-map.dir/20-map/20-map.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/20-map.dir/20-map/20-map.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/20-map/20-map.cpp

CMakeFiles/20-map.dir/20-map/20-map.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/20-map.dir/20-map/20-map.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/20-map/20-map.cpp > CMakeFiles/20-map.dir/20-map/20-map.i

CMakeFiles/20-map.dir/20-map/20-map.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/20-map.dir/20-map/20-map.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/20-map/20-map.cpp -o CMakeFiles/20-map.dir/20-map/20-map.s

CMakeFiles/20-map.dir/20-map/20-map.o.requires:

.PHONY : CMakeFiles/20-map.dir/20-map/20-map.o.requires

CMakeFiles/20-map.dir/20-map/20-map.o.provides: CMakeFiles/20-map.dir/20-map/20-map.o.requires
	$(MAKE) -f CMakeFiles/20-map.dir/build.make CMakeFiles/20-map.dir/20-map/20-map.o.provides.build
.PHONY : CMakeFiles/20-map.dir/20-map/20-map.o.provides

CMakeFiles/20-map.dir/20-map/20-map.o.provides.build: CMakeFiles/20-map.dir/20-map/20-map.o


# Object files for target 20-map
20__map_OBJECTS = \
"CMakeFiles/20-map.dir/20-map/20-map.o"

# External object files for target 20-map
20__map_EXTERNAL_OBJECTS =

20-map: CMakeFiles/20-map.dir/20-map/20-map.o
20-map: CMakeFiles/20-map.dir/build.make
20-map: CMakeFiles/20-map.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 20-map"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/20-map.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/20-map.dir/build: 20-map

.PHONY : CMakeFiles/20-map.dir/build

CMakeFiles/20-map.dir/requires: CMakeFiles/20-map.dir/20-map/20-map.o.requires

.PHONY : CMakeFiles/20-map.dir/requires

CMakeFiles/20-map.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/20-map.dir/cmake_clean.cmake
.PHONY : CMakeFiles/20-map.dir/clean

CMakeFiles/20-map.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles/20-map.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/20-map.dir/depend

