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
include CMakeFiles/julia.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/julia.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/julia.dir/flags.make

CMakeFiles/julia.dir/src/julia/julia.cpp.o: CMakeFiles/julia.dir/flags.make
CMakeFiles/julia.dir/src/julia/julia.cpp.o: src/julia/julia.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fzhan/Downloads/sb6code-master/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/julia.dir/src/julia/julia.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/julia.dir/src/julia/julia.cpp.o -c /home/fzhan/Downloads/sb6code-master/src/julia/julia.cpp

CMakeFiles/julia.dir/src/julia/julia.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/julia.dir/src/julia/julia.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fzhan/Downloads/sb6code-master/src/julia/julia.cpp > CMakeFiles/julia.dir/src/julia/julia.cpp.i

CMakeFiles/julia.dir/src/julia/julia.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/julia.dir/src/julia/julia.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fzhan/Downloads/sb6code-master/src/julia/julia.cpp -o CMakeFiles/julia.dir/src/julia/julia.cpp.s

CMakeFiles/julia.dir/src/julia/julia.cpp.o.requires:
.PHONY : CMakeFiles/julia.dir/src/julia/julia.cpp.o.requires

CMakeFiles/julia.dir/src/julia/julia.cpp.o.provides: CMakeFiles/julia.dir/src/julia/julia.cpp.o.requires
	$(MAKE) -f CMakeFiles/julia.dir/build.make CMakeFiles/julia.dir/src/julia/julia.cpp.o.provides.build
.PHONY : CMakeFiles/julia.dir/src/julia/julia.cpp.o.provides

CMakeFiles/julia.dir/src/julia/julia.cpp.o.provides.build: CMakeFiles/julia.dir/src/julia/julia.cpp.o

# Object files for target julia
julia_OBJECTS = \
"CMakeFiles/julia.dir/src/julia/julia.cpp.o"

# External object files for target julia
julia_EXTERNAL_OBJECTS =

bin/julia: CMakeFiles/julia.dir/src/julia/julia.cpp.o
bin/julia: lib/libsb6.a
bin/julia: CMakeFiles/julia.dir/build.make
bin/julia: CMakeFiles/julia.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/julia"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/julia.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/julia.dir/build: bin/julia
.PHONY : CMakeFiles/julia.dir/build

CMakeFiles/julia.dir/requires: CMakeFiles/julia.dir/src/julia/julia.cpp.o.requires
.PHONY : CMakeFiles/julia.dir/requires

CMakeFiles/julia.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/julia.dir/cmake_clean.cmake
.PHONY : CMakeFiles/julia.dir/clean

CMakeFiles/julia.dir/depend:
	cd /home/fzhan/Downloads/sb6code-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master/CMakeFiles/julia.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/julia.dir/depend

