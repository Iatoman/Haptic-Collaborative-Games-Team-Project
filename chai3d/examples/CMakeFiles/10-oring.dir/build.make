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
include CMakeFiles/10-oring.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/10-oring.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/10-oring.dir/flags.make

CMakeFiles/10-oring.dir/10-oring/10-oring.o: CMakeFiles/10-oring.dir/flags.make
CMakeFiles/10-oring.dir/10-oring/10-oring.o: GLFW/10-oring/10-oring.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/10-oring.dir/10-oring/10-oring.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/10-oring.dir/10-oring/10-oring.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/10-oring/10-oring.cpp

CMakeFiles/10-oring.dir/10-oring/10-oring.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/10-oring.dir/10-oring/10-oring.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/10-oring/10-oring.cpp > CMakeFiles/10-oring.dir/10-oring/10-oring.i

CMakeFiles/10-oring.dir/10-oring/10-oring.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/10-oring.dir/10-oring/10-oring.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/10-oring/10-oring.cpp -o CMakeFiles/10-oring.dir/10-oring/10-oring.s

CMakeFiles/10-oring.dir/10-oring/10-oring.o.requires:

.PHONY : CMakeFiles/10-oring.dir/10-oring/10-oring.o.requires

CMakeFiles/10-oring.dir/10-oring/10-oring.o.provides: CMakeFiles/10-oring.dir/10-oring/10-oring.o.requires
	$(MAKE) -f CMakeFiles/10-oring.dir/build.make CMakeFiles/10-oring.dir/10-oring/10-oring.o.provides.build
.PHONY : CMakeFiles/10-oring.dir/10-oring/10-oring.o.provides

CMakeFiles/10-oring.dir/10-oring/10-oring.o.provides.build: CMakeFiles/10-oring.dir/10-oring/10-oring.o


# Object files for target 10-oring
10__oring_OBJECTS = \
"CMakeFiles/10-oring.dir/10-oring/10-oring.o"

# External object files for target 10-oring
10__oring_EXTERNAL_OBJECTS =

10-oring: CMakeFiles/10-oring.dir/10-oring/10-oring.o
10-oring: CMakeFiles/10-oring.dir/build.make
10-oring: CMakeFiles/10-oring.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 10-oring"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/10-oring.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/10-oring.dir/build: 10-oring

.PHONY : CMakeFiles/10-oring.dir/build

CMakeFiles/10-oring.dir/requires: CMakeFiles/10-oring.dir/10-oring/10-oring.o.requires

.PHONY : CMakeFiles/10-oring.dir/requires

CMakeFiles/10-oring.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/10-oring.dir/cmake_clean.cmake
.PHONY : CMakeFiles/10-oring.dir/clean

CMakeFiles/10-oring.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles/10-oring.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/10-oring.dir/depend

