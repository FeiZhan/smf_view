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
include CMakeFiles/cubemapenv.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cubemapenv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cubemapenv.dir/flags.make

CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o: CMakeFiles/cubemapenv.dir/flags.make
CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o: src/cubemapenv/cubemapenv.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fzhan/Downloads/sb6code-master/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o -c /home/fzhan/Downloads/sb6code-master/src/cubemapenv/cubemapenv.cpp

CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fzhan/Downloads/sb6code-master/src/cubemapenv/cubemapenv.cpp > CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.i

CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fzhan/Downloads/sb6code-master/src/cubemapenv/cubemapenv.cpp -o CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.s

CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o.requires:
.PHONY : CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o.requires

CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o.provides: CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o.requires
	$(MAKE) -f CMakeFiles/cubemapenv.dir/build.make CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o.provides.build
.PHONY : CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o.provides

CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o.provides.build: CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o

# Object files for target cubemapenv
cubemapenv_OBJECTS = \
"CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o"

# External object files for target cubemapenv
cubemapenv_EXTERNAL_OBJECTS =

bin/cubemapenv: CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o
bin/cubemapenv: lib/libsb6.a
bin/cubemapenv: CMakeFiles/cubemapenv.dir/build.make
bin/cubemapenv: CMakeFiles/cubemapenv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/cubemapenv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cubemapenv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cubemapenv.dir/build: bin/cubemapenv
.PHONY : CMakeFiles/cubemapenv.dir/build

CMakeFiles/cubemapenv.dir/requires: CMakeFiles/cubemapenv.dir/src/cubemapenv/cubemapenv.cpp.o.requires
.PHONY : CMakeFiles/cubemapenv.dir/requires

CMakeFiles/cubemapenv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cubemapenv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cubemapenv.dir/clean

CMakeFiles/cubemapenv.dir/depend:
	cd /home/fzhan/Downloads/sb6code-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master /home/fzhan/Downloads/sb6code-master/CMakeFiles/cubemapenv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cubemapenv.dir/depend

