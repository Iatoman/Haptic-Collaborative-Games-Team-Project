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
include CMakeFiles/24-turntable.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/24-turntable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/24-turntable.dir/flags.make

CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o: CMakeFiles/24-turntable.dir/flags.make
CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o: GLFW/24-turntable/24-turntable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/24-turntable/24-turntable.cpp

CMakeFiles/24-turntable.dir/24-turntable/24-turntable.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/24-turntable.dir/24-turntable/24-turntable.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/24-turntable/24-turntable.cpp > CMakeFiles/24-turntable.dir/24-turntable/24-turntable.i

CMakeFiles/24-turntable.dir/24-turntable/24-turntable.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/24-turntable.dir/24-turntable/24-turntable.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/24-turntable/24-turntable.cpp -o CMakeFiles/24-turntable.dir/24-turntable/24-turntable.s

CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o.requires:

.PHONY : CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o.requires

CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o.provides: CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o.requires
	$(MAKE) -f CMakeFiles/24-turntable.dir/build.make CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o.provides.build
.PHONY : CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o.provides

CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o.provides.build: CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o


# Object files for target 24-turntable
24__turntable_OBJECTS = \
"CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o"

# External object files for target 24-turntable
24__turntable_EXTERNAL_OBJECTS =

24-turntable: CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o
24-turntable: CMakeFiles/24-turntable.dir/build.make
24-turntable: CMakeFiles/24-turntable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 24-turntable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/24-turntable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/24-turntable.dir/build: 24-turntable

.PHONY : CMakeFiles/24-turntable.dir/build

CMakeFiles/24-turntable.dir/requires: CMakeFiles/24-turntable.dir/24-turntable/24-turntable.o.requires

.PHONY : CMakeFiles/24-turntable.dir/requires

CMakeFiles/24-turntable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/24-turntable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/24-turntable.dir/clean

CMakeFiles/24-turntable.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles/24-turntable.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/24-turntable.dir/depend

