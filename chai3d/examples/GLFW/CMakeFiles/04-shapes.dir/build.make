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
include examples/GLFW/CMakeFiles/04-shapes.dir/depend.make

# Include the progress variables for this target.
include examples/GLFW/CMakeFiles/04-shapes.dir/progress.make

# Include the compile flags for this target's objects.
include examples/GLFW/CMakeFiles/04-shapes.dir/flags.make

examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o: examples/GLFW/CMakeFiles/04-shapes.dir/flags.make
examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o: examples/GLFW/04-shapes/04-shapes.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/04-shapes/04-shapes.cpp

examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.i"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/04-shapes/04-shapes.cpp > CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.i

examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.s"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/04-shapes/04-shapes.cpp -o CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.s

examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o.requires:

.PHONY : examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o.requires

examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o.provides: examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o.requires
	$(MAKE) -f examples/GLFW/CMakeFiles/04-shapes.dir/build.make examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o.provides.build
.PHONY : examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o.provides

examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o.provides.build: examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o


# Object files for target 04-shapes
04__shapes_OBJECTS = \
"CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o"

# External object files for target 04-shapes
04__shapes_EXTERNAL_OBJECTS =

bin/lin-x86_64/04-shapes: examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o
bin/lin-x86_64/04-shapes: examples/GLFW/CMakeFiles/04-shapes.dir/build.make
bin/lin-x86_64/04-shapes: libchai3d.a
bin/lin-x86_64/04-shapes: /usr/lib/x86_64-linux-gnu/libGL.so
bin/lin-x86_64/04-shapes: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/lin-x86_64/04-shapes: extras/GLFW/libglfw.a
bin/lin-x86_64/04-shapes: /usr/lib/x86_64-linux-gnu/libGL.so
bin/lin-x86_64/04-shapes: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/lin-x86_64/04-shapes: examples/GLFW/CMakeFiles/04-shapes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/lin-x86_64/04-shapes"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/04-shapes.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/GLFW/CMakeFiles/04-shapes.dir/build: bin/lin-x86_64/04-shapes

.PHONY : examples/GLFW/CMakeFiles/04-shapes.dir/build

examples/GLFW/CMakeFiles/04-shapes.dir/requires: examples/GLFW/CMakeFiles/04-shapes.dir/04-shapes/04-shapes.cpp.o.requires

.PHONY : examples/GLFW/CMakeFiles/04-shapes.dir/requires

examples/GLFW/CMakeFiles/04-shapes.dir/clean:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && $(CMAKE_COMMAND) -P CMakeFiles/04-shapes.dir/cmake_clean.cmake
.PHONY : examples/GLFW/CMakeFiles/04-shapes.dir/clean

examples/GLFW/CMakeFiles/04-shapes.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/CMakeFiles/04-shapes.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/GLFW/CMakeFiles/04-shapes.dir/depend
