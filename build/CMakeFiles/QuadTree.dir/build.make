# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.16.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.16.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Jessica/git/QuadTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Jessica/git/QuadTree/build

# Include any dependencies generated for this target.
include CMakeFiles/QuadTree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/QuadTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/QuadTree.dir/flags.make

CMakeFiles/QuadTree.dir/main.cpp.o: CMakeFiles/QuadTree.dir/flags.make
CMakeFiles/QuadTree.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jessica/git/QuadTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/QuadTree.dir/main.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QuadTree.dir/main.cpp.o -c /Users/Jessica/git/QuadTree/main.cpp

CMakeFiles/QuadTree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QuadTree.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jessica/git/QuadTree/main.cpp > CMakeFiles/QuadTree.dir/main.cpp.i

CMakeFiles/QuadTree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QuadTree.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jessica/git/QuadTree/main.cpp -o CMakeFiles/QuadTree.dir/main.cpp.s

CMakeFiles/QuadTree.dir/Node.cpp.o: CMakeFiles/QuadTree.dir/flags.make
CMakeFiles/QuadTree.dir/Node.cpp.o: ../Node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jessica/git/QuadTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/QuadTree.dir/Node.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QuadTree.dir/Node.cpp.o -c /Users/Jessica/git/QuadTree/Node.cpp

CMakeFiles/QuadTree.dir/Node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QuadTree.dir/Node.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jessica/git/QuadTree/Node.cpp > CMakeFiles/QuadTree.dir/Node.cpp.i

CMakeFiles/QuadTree.dir/Node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QuadTree.dir/Node.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jessica/git/QuadTree/Node.cpp -o CMakeFiles/QuadTree.dir/Node.cpp.s

CMakeFiles/QuadTree.dir/QuadTree.cpp.o: CMakeFiles/QuadTree.dir/flags.make
CMakeFiles/QuadTree.dir/QuadTree.cpp.o: ../QuadTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jessica/git/QuadTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/QuadTree.dir/QuadTree.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QuadTree.dir/QuadTree.cpp.o -c /Users/Jessica/git/QuadTree/QuadTree.cpp

CMakeFiles/QuadTree.dir/QuadTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QuadTree.dir/QuadTree.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jessica/git/QuadTree/QuadTree.cpp > CMakeFiles/QuadTree.dir/QuadTree.cpp.i

CMakeFiles/QuadTree.dir/QuadTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QuadTree.dir/QuadTree.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jessica/git/QuadTree/QuadTree.cpp -o CMakeFiles/QuadTree.dir/QuadTree.cpp.s

CMakeFiles/QuadTree.dir/Square.cpp.o: CMakeFiles/QuadTree.dir/flags.make
CMakeFiles/QuadTree.dir/Square.cpp.o: ../Square.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jessica/git/QuadTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/QuadTree.dir/Square.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QuadTree.dir/Square.cpp.o -c /Users/Jessica/git/QuadTree/Square.cpp

CMakeFiles/QuadTree.dir/Square.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QuadTree.dir/Square.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jessica/git/QuadTree/Square.cpp > CMakeFiles/QuadTree.dir/Square.cpp.i

CMakeFiles/QuadTree.dir/Square.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QuadTree.dir/Square.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jessica/git/QuadTree/Square.cpp -o CMakeFiles/QuadTree.dir/Square.cpp.s

CMakeFiles/QuadTree.dir/Point.cpp.o: CMakeFiles/QuadTree.dir/flags.make
CMakeFiles/QuadTree.dir/Point.cpp.o: ../Point.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jessica/git/QuadTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/QuadTree.dir/Point.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QuadTree.dir/Point.cpp.o -c /Users/Jessica/git/QuadTree/Point.cpp

CMakeFiles/QuadTree.dir/Point.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QuadTree.dir/Point.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jessica/git/QuadTree/Point.cpp > CMakeFiles/QuadTree.dir/Point.cpp.i

CMakeFiles/QuadTree.dir/Point.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QuadTree.dir/Point.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jessica/git/QuadTree/Point.cpp -o CMakeFiles/QuadTree.dir/Point.cpp.s

# Object files for target QuadTree
QuadTree_OBJECTS = \
"CMakeFiles/QuadTree.dir/main.cpp.o" \
"CMakeFiles/QuadTree.dir/Node.cpp.o" \
"CMakeFiles/QuadTree.dir/QuadTree.cpp.o" \
"CMakeFiles/QuadTree.dir/Square.cpp.o" \
"CMakeFiles/QuadTree.dir/Point.cpp.o"

# External object files for target QuadTree
QuadTree_EXTERNAL_OBJECTS =

QuadTree: CMakeFiles/QuadTree.dir/main.cpp.o
QuadTree: CMakeFiles/QuadTree.dir/Node.cpp.o
QuadTree: CMakeFiles/QuadTree.dir/QuadTree.cpp.o
QuadTree: CMakeFiles/QuadTree.dir/Square.cpp.o
QuadTree: CMakeFiles/QuadTree.dir/Point.cpp.o
QuadTree: CMakeFiles/QuadTree.dir/build.make
QuadTree: CMakeFiles/QuadTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Jessica/git/QuadTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable QuadTree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QuadTree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/QuadTree.dir/build: QuadTree

.PHONY : CMakeFiles/QuadTree.dir/build

CMakeFiles/QuadTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QuadTree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QuadTree.dir/clean

CMakeFiles/QuadTree.dir/depend:
	cd /Users/Jessica/git/QuadTree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Jessica/git/QuadTree /Users/Jessica/git/QuadTree /Users/Jessica/git/QuadTree/build /Users/Jessica/git/QuadTree/build /Users/Jessica/git/QuadTree/build/CMakeFiles/QuadTree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/QuadTree.dir/depend
