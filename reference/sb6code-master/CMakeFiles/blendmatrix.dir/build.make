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
include CMakeFiles/blendmatrix.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/blendmatrix.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/blendmatrix.dir/flags.make

CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o: CMakeFiles/blendmatrix.dir/flags.make
CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o: src/blendmatrix/blendmatrix.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fzhan/Downloads/sb6code-master/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o -c /home/fzhan/Downloads/sb6code-master/src/blendmatrix/blendmatrix.cpp

CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fzhan/Downloads/sb6code-master/src/blendmatrix/blendmatrix.cpp > CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.i

CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fzhan/Downloads/sb6code-master/src/blendmatrix/blendmatrix.cpp -o CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.s

CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o.requires:
.PHONY : CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o.requires

CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o.provides: CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o.requires
	$(MAKE) -f CMakeFiles/blendmatrix.dir/build.make CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o.provides.build
.PHONY : CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o.provides

CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o.provides.build: CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o

# Object files for target blendmatrix
blendmatrix_OBJECTS = \
"CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o"

# External object files for target blendmatrix
blendmatrix_EXTERNAL_OBJECTS =

bin/blendmatrix: CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o
bin/blendmatrix: lib/libsb6.a
bin/blendmatrix: CMakeFiles/blendmatrix.dir/build.make
bin/blendmatrix: CMakeFiles/blendmatrix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/blendmatrix"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/blendmatrix.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/blendmatrix.dir/build: bin/blendmatrix
.PHONY : CMakeFiles/blendmatrix.dir/build

CMakeFiles/blendmatrix.dir/requires: CMakeFiles/blendmatrix.dir/src/blendmatrix/blendmatrix.cpp.o.requires
.PHONY : CMakeFiles/blendmatrix.dir/requires

CMakeFiles/blendmatrix.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/blendmatrix.dir/cmake_clean.cmake
.PHONY : CMakeFiles/blendmatrix.dir/clean

CMakeFiles/blendmatrix.dir/depend:
	cd /home/fzhan/Downloads/sb6code-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master/CMakeFiles/blendmatrix.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/blendmatrix.dir/depend

