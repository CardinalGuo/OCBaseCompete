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
CMAKE_SOURCE_DIR = /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build

# Include any dependencies generated for this target.
include test/CMakeFiles/client_performance_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/client_performance_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/client_performance_test.dir/flags.make

test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o: test/CMakeFiles/client_performance_test.dir/flags.make
test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o: ../test/client_performance_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o"
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/test && /usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o -c /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/test/client_performance_test.cpp

test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_performance_test.dir/client_performance_test.cpp.i"
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/test && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/test/client_performance_test.cpp > CMakeFiles/client_performance_test.dir/client_performance_test.cpp.i

test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_performance_test.dir/client_performance_test.cpp.s"
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/test && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/test/client_performance_test.cpp -o CMakeFiles/client_performance_test.dir/client_performance_test.cpp.s

test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o.requires:

.PHONY : test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o.requires

test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o.provides: test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/client_performance_test.dir/build.make test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o.provides.build
.PHONY : test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o.provides

test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o.provides.build: test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o


# Object files for target client_performance_test
client_performance_test_OBJECTS = \
"CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o"

# External object files for target client_performance_test
client_performance_test_EXTERNAL_OBJECTS =

bin/client_performance_test: test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o
bin/client_performance_test: test/CMakeFiles/client_performance_test.dir/build.make
bin/client_performance_test: lib/libobserver.a
bin/client_performance_test: lib/libcommon.so.1.0.0
bin/client_performance_test: test/CMakeFiles/client_performance_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/client_performance_test"
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_performance_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/client_performance_test.dir/build: bin/client_performance_test

.PHONY : test/CMakeFiles/client_performance_test.dir/build

test/CMakeFiles/client_performance_test.dir/requires: test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o.requires

.PHONY : test/CMakeFiles/client_performance_test.dir/requires

test/CMakeFiles/client_performance_test.dir/clean:
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/test && $(CMAKE_COMMAND) -P CMakeFiles/client_performance_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/client_performance_test.dir/clean

test/CMakeFiles/client_performance_test.dir/depend:
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/test /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/test /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/test/CMakeFiles/client_performance_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/client_performance_test.dir/depend

