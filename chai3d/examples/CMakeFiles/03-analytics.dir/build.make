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
include CMakeFiles/03-analytics.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/03-analytics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/03-analytics.dir/flags.make

CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o: CMakeFiles/03-analytics.dir/flags.make
CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o: GLFW/03-analytics/03-analytics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/03-analytics/03-analytics.cpp

CMakeFiles/03-analytics.dir/03-analytics/03-analytics.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/03-analytics.dir/03-analytics/03-analytics.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/03-analytics/03-analytics.cpp > CMakeFiles/03-analytics.dir/03-analytics/03-analytics.i

CMakeFiles/03-analytics.dir/03-analytics/03-analytics.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/03-analytics.dir/03-analytics/03-analytics.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/03-analytics/03-analytics.cpp -o CMakeFiles/03-analytics.dir/03-analytics/03-analytics.s

CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o.requires:

.PHONY : CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o.requires

CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o.provides: CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o.requires
	$(MAKE) -f CMakeFiles/03-analytics.dir/build.make CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o.provides.build
.PHONY : CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o.provides

CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o.provides.build: CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o


# Object files for target 03-analytics
03__analytics_OBJECTS = \
"CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o"

# External object files for target 03-analytics
03__analytics_EXTERNAL_OBJECTS =

03-analytics: CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o
03-analytics: CMakeFiles/03-analytics.dir/build.make
03-analytics: CMakeFiles/03-analytics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 03-analytics"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/03-analytics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/03-analytics.dir/build: 03-analytics

.PHONY : CMakeFiles/03-analytics.dir/build

CMakeFiles/03-analytics.dir/requires: CMakeFiles/03-analytics.dir/03-analytics/03-analytics.o.requires

.PHONY : CMakeFiles/03-analytics.dir/requires

CMakeFiles/03-analytics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/03-analytics.dir/cmake_clean.cmake
.PHONY : CMakeFiles/03-analytics.dir/clean

CMakeFiles/03-analytics.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles/03-analytics.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/03-analytics.dir/depend

