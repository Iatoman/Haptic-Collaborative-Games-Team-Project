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
CMAKE_SOURCE_DIR = /home/cs_group_2021_21/Desktop/chai3d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cs_group_2021_21/Desktop/chai3d

# Include any dependencies generated for this target.
include examples/GLFW/CMakeFiles/12-polygons.dir/depend.make

# Include the progress variables for this target.
include examples/GLFW/CMakeFiles/12-polygons.dir/progress.make

# Include the compile flags for this target's objects.
include examples/GLFW/CMakeFiles/12-polygons.dir/flags.make

examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o: examples/GLFW/CMakeFiles/12-polygons.dir/flags.make
examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o: examples/GLFW/12-polygons/12-polygons.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/12-polygons/12-polygons.cpp

examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.i"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/12-polygons/12-polygons.cpp > CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.i

examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.s"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/12-polygons/12-polygons.cpp -o CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.s

examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o.requires:

.PHONY : examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o.requires

examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o.provides: examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o.requires
	$(MAKE) -f examples/GLFW/CMakeFiles/12-polygons.dir/build.make examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o.provides.build
.PHONY : examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o.provides

examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o.provides.build: examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o


# Object files for target 12-polygons
12__polygons_OBJECTS = \
"CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o"

# External object files for target 12-polygons
12__polygons_EXTERNAL_OBJECTS =

bin/lin-x86_64/12-polygons: examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o
bin/lin-x86_64/12-polygons: examples/GLFW/CMakeFiles/12-polygons.dir/build.make
bin/lin-x86_64/12-polygons: libchai3d.a
bin/lin-x86_64/12-polygons: /usr/lib/x86_64-linux-gnu/libGL.so
bin/lin-x86_64/12-polygons: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/lin-x86_64/12-polygons: extras/GLFW/libglfw.a
bin/lin-x86_64/12-polygons: /usr/lib/x86_64-linux-gnu/libGL.so
bin/lin-x86_64/12-polygons: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/lin-x86_64/12-polygons: examples/GLFW/CMakeFiles/12-polygons.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/lin-x86_64/12-polygons"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/12-polygons.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/GLFW/CMakeFiles/12-polygons.dir/build: bin/lin-x86_64/12-polygons

.PHONY : examples/GLFW/CMakeFiles/12-polygons.dir/build

examples/GLFW/CMakeFiles/12-polygons.dir/requires: examples/GLFW/CMakeFiles/12-polygons.dir/12-polygons/12-polygons.cpp.o.requires

.PHONY : examples/GLFW/CMakeFiles/12-polygons.dir/requires

examples/GLFW/CMakeFiles/12-polygons.dir/clean:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && $(CMAKE_COMMAND) -P CMakeFiles/12-polygons.dir/cmake_clean.cmake
.PHONY : examples/GLFW/CMakeFiles/12-polygons.dir/clean

examples/GLFW/CMakeFiles/12-polygons.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/CMakeFiles/12-polygons.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/GLFW/CMakeFiles/12-polygons.dir/depend

