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
include CMakeFiles/32-myproject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/32-myproject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/32-myproject.dir/flags.make

CMakeFiles/32-myproject.dir/32-myproject/11-effects.o: CMakeFiles/32-myproject.dir/flags.make
CMakeFiles/32-myproject.dir/32-myproject/11-effects.o: GLFW/32-myproject/11-effects.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/32-myproject.dir/32-myproject/11-effects.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/32-myproject.dir/32-myproject/11-effects.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/32-myproject/11-effects.cpp

CMakeFiles/32-myproject.dir/32-myproject/11-effects.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/32-myproject.dir/32-myproject/11-effects.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/32-myproject/11-effects.cpp > CMakeFiles/32-myproject.dir/32-myproject/11-effects.i

CMakeFiles/32-myproject.dir/32-myproject/11-effects.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/32-myproject.dir/32-myproject/11-effects.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/32-myproject/11-effects.cpp -o CMakeFiles/32-myproject.dir/32-myproject/11-effects.s

CMakeFiles/32-myproject.dir/32-myproject/11-effects.o.requires:

.PHONY : CMakeFiles/32-myproject.dir/32-myproject/11-effects.o.requires

CMakeFiles/32-myproject.dir/32-myproject/11-effects.o.provides: CMakeFiles/32-myproject.dir/32-myproject/11-effects.o.requires
	$(MAKE) -f CMakeFiles/32-myproject.dir/build.make CMakeFiles/32-myproject.dir/32-myproject/11-effects.o.provides.build
.PHONY : CMakeFiles/32-myproject.dir/32-myproject/11-effects.o.provides

CMakeFiles/32-myproject.dir/32-myproject/11-effects.o.provides.build: CMakeFiles/32-myproject.dir/32-myproject/11-effects.o


# Object files for target 32-myproject
32__myproject_OBJECTS = \
"CMakeFiles/32-myproject.dir/32-myproject/11-effects.o"

# External object files for target 32-myproject
32__myproject_EXTERNAL_OBJECTS =

32-myproject: CMakeFiles/32-myproject.dir/32-myproject/11-effects.o
32-myproject: CMakeFiles/32-myproject.dir/build.make
32-myproject: CMakeFiles/32-myproject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 32-myproject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/32-myproject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/32-myproject.dir/build: 32-myproject

.PHONY : CMakeFiles/32-myproject.dir/build

CMakeFiles/32-myproject.dir/requires: CMakeFiles/32-myproject.dir/32-myproject/11-effects.o.requires

.PHONY : CMakeFiles/32-myproject.dir/requires

CMakeFiles/32-myproject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/32-myproject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/32-myproject.dir/clean

CMakeFiles/32-myproject.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles/32-myproject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/32-myproject.dir/depend

