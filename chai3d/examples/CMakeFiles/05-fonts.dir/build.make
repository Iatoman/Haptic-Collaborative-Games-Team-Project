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
include CMakeFiles/05-fonts.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/05-fonts.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/05-fonts.dir/flags.make

CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o: CMakeFiles/05-fonts.dir/flags.make
CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o: GLFW/05-fonts/05-fonts.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o -c /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/05-fonts/05-fonts.cpp

CMakeFiles/05-fonts.dir/05-fonts/05-fonts.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/05-fonts.dir/05-fonts/05-fonts.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/05-fonts/05-fonts.cpp > CMakeFiles/05-fonts.dir/05-fonts/05-fonts.i

CMakeFiles/05-fonts.dir/05-fonts/05-fonts.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/05-fonts.dir/05-fonts/05-fonts.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW/05-fonts/05-fonts.cpp -o CMakeFiles/05-fonts.dir/05-fonts/05-fonts.s

CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o.requires:

.PHONY : CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o.requires

CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o.provides: CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o.requires
	$(MAKE) -f CMakeFiles/05-fonts.dir/build.make CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o.provides.build
.PHONY : CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o.provides

CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o.provides.build: CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o


# Object files for target 05-fonts
05__fonts_OBJECTS = \
"CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o"

# External object files for target 05-fonts
05__fonts_EXTERNAL_OBJECTS =

05-fonts: CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o
05-fonts: CMakeFiles/05-fonts.dir/build.make
05-fonts: CMakeFiles/05-fonts.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 05-fonts"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/05-fonts.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/05-fonts.dir/build: 05-fonts

.PHONY : CMakeFiles/05-fonts.dir/build

CMakeFiles/05-fonts.dir/requires: CMakeFiles/05-fonts.dir/05-fonts/05-fonts.o.requires

.PHONY : CMakeFiles/05-fonts.dir/requires

CMakeFiles/05-fonts.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/05-fonts.dir/cmake_clean.cmake
.PHONY : CMakeFiles/05-fonts.dir/clean

CMakeFiles/05-fonts.dir/depend:
	cd /home/cs_group_2021_21/Desktop/chai3d/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples/GLFW /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples /home/cs_group_2021_21/Desktop/chai3d/examples/CMakeFiles/05-fonts.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/05-fonts.dir/depend

