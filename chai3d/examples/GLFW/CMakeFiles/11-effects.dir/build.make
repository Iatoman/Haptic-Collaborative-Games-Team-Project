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
include examples/GLFW/CMakeFiles/11-effects.dir/depend.make

# Include the progress variables for this target.
include examples/GLFW/CMakeFiles/11-effects.dir/progress.make

# Include the compile flags for this target's objects.
include examples/GLFW/CMakeFiles/11-effects.dir/flags.make

examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o: examples/GLFW/CMakeFiles/11-effects.dir/flags.make
examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o: examples/GLFW/11-effects/11-effects.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/11-effects/11-effects.cpp

examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.i"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/11-effects/11-effects.cpp > CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.i

examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.s"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/11-effects/11-effects.cpp -o CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.s

examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o.requires:

.PHONY : examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o.requires

examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o.provides: examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o.requires
	$(MAKE) -f examples/GLFW/CMakeFiles/11-effects.dir/build.make examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o.provides.build
.PHONY : examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o.provides

examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o.provides.build: examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o


# Object files for target 11-effects
11__effects_OBJECTS = \
"CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o"

# External object files for target 11-effects
11__effects_EXTERNAL_OBJECTS =

bin/lin-x86_64/11-effects: examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o
bin/lin-x86_64/11-effects: examples/GLFW/CMakeFiles/11-effects.dir/build.make
bin/lin-x86_64/11-effects: libchai3d.a
bin/lin-x86_64/11-effects: /usr/lib/x86_64-linux-gnu/libGL.so
bin/lin-x86_64/11-effects: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/lin-x86_64/11-effects: extras/GLFW/libglfw.a
bin/lin-x86_64/11-effects: /usr/lib/x86_64-linux-gnu/libGL.so
bin/lin-x86_64/11-effects: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/lin-x86_64/11-effects: examples/GLFW/CMakeFiles/11-effects.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/lin-x86_64/11-effects"
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/11-effects.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/GLFW/CMakeFiles/11-effects.dir/build: bin/lin-x86_64/11-effects

.PHONY : examples/GLFW/CMakeFiles/11-effects.dir/build

examples/GLFW/CMakeFiles/11-effects.dir/requires: examples/GLFW/CMakeFiles/11-effects.dir/11-effects/11-effects.cpp.o.requires

.PHONY : examples/GLFW/CMakeFiles/11-effects.dir/requires

examples/GLFW/CMakeFiles/11-effects.dir/clean:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW && $(CMAKE_COMMAND) -P CMakeFiles/11-effects.dir/cmake_clean.cmake
.PHONY : examples/GLFW/CMakeFiles/11-effects.dir/clean

examples/GLFW/CMakeFiles/11-effects.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/CMakeFiles/11-effects.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/GLFW/CMakeFiles/11-effects.dir/depend

