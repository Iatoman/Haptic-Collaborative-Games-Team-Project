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
include CMakeFiles/09-magnets.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/09-magnets.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/09-magnets.dir/flags.make

CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o: CMakeFiles/09-magnets.dir/flags.make
CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o: GLFW/09-magnets/09-magnets.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/09-magnets/09-magnets.cpp

CMakeFiles/09-magnets.dir/09-magnets/09-magnets.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/09-magnets.dir/09-magnets/09-magnets.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/09-magnets/09-magnets.cpp > CMakeFiles/09-magnets.dir/09-magnets/09-magnets.i

CMakeFiles/09-magnets.dir/09-magnets/09-magnets.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/09-magnets.dir/09-magnets/09-magnets.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/09-magnets/09-magnets.cpp -o CMakeFiles/09-magnets.dir/09-magnets/09-magnets.s

CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o.requires:

.PHONY : CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o.requires

CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o.provides: CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o.requires
	$(MAKE) -f CMakeFiles/09-magnets.dir/build.make CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o.provides.build
.PHONY : CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o.provides

CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o.provides.build: CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o


# Object files for target 09-magnets
09__magnets_OBJECTS = \
"CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o"

# External object files for target 09-magnets
09__magnets_EXTERNAL_OBJECTS =

09-magnets: CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o
09-magnets: CMakeFiles/09-magnets.dir/build.make
09-magnets: CMakeFiles/09-magnets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 09-magnets"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/09-magnets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/09-magnets.dir/build: 09-magnets

.PHONY : CMakeFiles/09-magnets.dir/build

CMakeFiles/09-magnets.dir/requires: CMakeFiles/09-magnets.dir/09-magnets/09-magnets.o.requires

.PHONY : CMakeFiles/09-magnets.dir/requires

CMakeFiles/09-magnets.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/09-magnets.dir/cmake_clean.cmake
.PHONY : CMakeFiles/09-magnets.dir/clean

CMakeFiles/09-magnets.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles/09-magnets.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/09-magnets.dir/depend
