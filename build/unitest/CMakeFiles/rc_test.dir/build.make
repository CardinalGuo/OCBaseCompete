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
include unitest/CMakeFiles/rc_test.dir/depend.make

# Include the progress variables for this target.
include unitest/CMakeFiles/rc_test.dir/progress.make

# Include the compile flags for this target's objects.
include unitest/CMakeFiles/rc_test.dir/flags.make

unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o: unitest/CMakeFiles/rc_test.dir/flags.make
unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o: ../unitest/rc_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o"
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/unitest && /usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rc_test.dir/rc_test.cpp.o -c /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/unitest/rc_test.cpp

unitest/CMakeFiles/rc_test.dir/rc_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rc_test.dir/rc_test.cpp.i"
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/unitest && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/unitest/rc_test.cpp > CMakeFiles/rc_test.dir/rc_test.cpp.i

unitest/CMakeFiles/rc_test.dir/rc_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rc_test.dir/rc_test.cpp.s"
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/unitest && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/unitest/rc_test.cpp -o CMakeFiles/rc_test.dir/rc_test.cpp.s

unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o.requires:

.PHONY : unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o.requires

unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o.provides: unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o.requires
	$(MAKE) -f unitest/CMakeFiles/rc_test.dir/build.make unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o.provides.build
.PHONY : unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o.provides

unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o.provides.build: unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o


# Object files for target rc_test
rc_test_OBJECTS = \
"CMakeFiles/rc_test.dir/rc_test.cpp.o"

# External object files for target rc_test
rc_test_EXTERNAL_OBJECTS =

bin/rc_test: unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o
bin/rc_test: unitest/CMakeFiles/rc_test.dir/build.make
bin/rc_test: lib/libobserver.a
bin/rc_test: lib/libcommon.so.1.0.0
bin/rc_test: unitest/CMakeFiles/rc_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/rc_test"
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/unitest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rc_test.dir/link.txt --verbose=$(VERBOSE)
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/unitest && /usr/bin/cmake -D TEST_TARGET=rc_test -D TEST_EXECUTABLE=/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/bin/rc_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/unitest -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=rc_test_TESTS -D CTEST_FILE=/mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/unitest/rc_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -P /usr/share/cmake-3.10/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
unitest/CMakeFiles/rc_test.dir/build: bin/rc_test

.PHONY : unitest/CMakeFiles/rc_test.dir/build

unitest/CMakeFiles/rc_test.dir/requires: unitest/CMakeFiles/rc_test.dir/rc_test.cpp.o.requires

.PHONY : unitest/CMakeFiles/rc_test.dir/requires

unitest/CMakeFiles/rc_test.dir/clean:
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/unitest && $(CMAKE_COMMAND) -P CMakeFiles/rc_test.dir/cmake_clean.cmake
.PHONY : unitest/CMakeFiles/rc_test.dir/clean

unitest/CMakeFiles/rc_test.dir/depend:
	cd /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/unitest /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/unitest /mnt/c/Users/Pope_Guo/Desktop/miniob/OCBase/build/unitest/CMakeFiles/rc_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unitest/CMakeFiles/rc_test.dir/depend

