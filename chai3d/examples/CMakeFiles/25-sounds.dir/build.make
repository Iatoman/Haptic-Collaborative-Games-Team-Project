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
include CMakeFiles/25-sounds.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/25-sounds.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/25-sounds.dir/flags.make

CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o: CMakeFiles/25-sounds.dir/flags.make
CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o: GLFW/25-sounds/25-sounds.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/25-sounds/25-sounds.cpp

CMakeFiles/25-sounds.dir/25-sounds/25-sounds.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/25-sounds.dir/25-sounds/25-sounds.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/25-sounds/25-sounds.cpp > CMakeFiles/25-sounds.dir/25-sounds/25-sounds.i

CMakeFiles/25-sounds.dir/25-sounds/25-sounds.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/25-sounds.dir/25-sounds/25-sounds.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/25-sounds/25-sounds.cpp -o CMakeFiles/25-sounds.dir/25-sounds/25-sounds.s

CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o.requires:

.PHONY : CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o.requires

CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o.provides: CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o.requires
	$(MAKE) -f CMakeFiles/25-sounds.dir/build.make CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o.provides.build
.PHONY : CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o.provides

CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o.provides.build: CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o


# Object files for target 25-sounds
25__sounds_OBJECTS = \
"CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o"

# External object files for target 25-sounds
25__sounds_EXTERNAL_OBJECTS =

25-sounds: CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o
25-sounds: CMakeFiles/25-sounds.dir/build.make
25-sounds: CMakeFiles/25-sounds.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 25-sounds"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/25-sounds.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/25-sounds.dir/build: 25-sounds

.PHONY : CMakeFiles/25-sounds.dir/build

CMakeFiles/25-sounds.dir/requires: CMakeFiles/25-sounds.dir/25-sounds/25-sounds.o.requires

.PHONY : CMakeFiles/25-sounds.dir/requires

CMakeFiles/25-sounds.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/25-sounds.dir/cmake_clean.cmake
.PHONY : CMakeFiles/25-sounds.dir/clean

CMakeFiles/25-sounds.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles/25-sounds.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/25-sounds.dir/depend
