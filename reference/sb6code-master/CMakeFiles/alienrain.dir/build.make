# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fzhan/Downloads/sb6code-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fzhan/Downloads/sb6code-master

# Include any dependencies generated for this target.
include CMakeFiles/alienrain.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/alienrain.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/alienrain.dir/flags.make

CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o: CMakeFiles/alienrain.dir/flags.make
CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o: src/alienrain/alienrain.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fzhan/Downloads/sb6code-master/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o -c /home/fzhan/Downloads/sb6code-master/src/alienrain/alienrain.cpp

CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fzhan/Downloads/sb6code-master/src/alienrain/alienrain.cpp > CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.i

CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fzhan/Downloads/sb6code-master/src/alienrain/alienrain.cpp -o CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.s

CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o.requires:
.PHONY : CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o.requires

CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o.provides: CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o.requires
	$(MAKE) -f CMakeFiles/alienrain.dir/build.make CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o.provides.build
.PHONY : CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o.provides

CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o.provides.build: CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o

# Object files for target alienrain
alienrain_OBJECTS = \
"CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o"

# External object files for target alienrain
alienrain_EXTERNAL_OBJECTS =

bin/alienrain: CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o
bin/alienrain: lib/libsb6.a
bin/alienrain: CMakeFiles/alienrain.dir/build.make
bin/alienrain: CMakeFiles/alienrain.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/alienrain"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alienrain.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/alienrain.dir/build: bin/alienrain
.PHONY : CMakeFiles/alienrain.dir/build

CMakeFiles/alienrain.dir/requires: CMakeFiles/alienrain.dir/src/alienrain/alienrain.cpp.o.requires
.PHONY : CMakeFiles/alienrain.dir/requires

CMakeFiles/alienrain.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/alienrain.dir/cmake_clean.cmake
.PHONY : CMakeFiles/alienrain.dir/clean

CMakeFiles/alienrain.dir/depend:
	cd /home/fzhan/Downloads/sb6code-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master/CMakeFiles/alienrain.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/alienrain.dir/depend

