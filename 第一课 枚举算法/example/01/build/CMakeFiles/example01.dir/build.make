# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Evan/MyWorks/基础算法入门/example/01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Evan/MyWorks/基础算法入门/example/01/build

# Include any dependencies generated for this target.
include CMakeFiles/example01.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/example01.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/example01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/example01.dir/flags.make

CMakeFiles/example01.dir/main.cpp.o: CMakeFiles/example01.dir/flags.make
CMakeFiles/example01.dir/main.cpp.o: /home/Evan/MyWorks/基础算法入门/example/01/main.cpp
CMakeFiles/example01.dir/main.cpp.o: CMakeFiles/example01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/Evan/MyWorks/基础算法入门/example/01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/example01.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/example01.dir/main.cpp.o -MF CMakeFiles/example01.dir/main.cpp.o.d -o CMakeFiles/example01.dir/main.cpp.o -c /home/Evan/MyWorks/基础算法入门/example/01/main.cpp

CMakeFiles/example01.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/example01.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Evan/MyWorks/基础算法入门/example/01/main.cpp > CMakeFiles/example01.dir/main.cpp.i

CMakeFiles/example01.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/example01.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Evan/MyWorks/基础算法入门/example/01/main.cpp -o CMakeFiles/example01.dir/main.cpp.s

# Object files for target example01
example01_OBJECTS = \
"CMakeFiles/example01.dir/main.cpp.o"

# External object files for target example01
example01_EXTERNAL_OBJECTS =

example01: CMakeFiles/example01.dir/main.cpp.o
example01: CMakeFiles/example01.dir/build.make
example01: CMakeFiles/example01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/Evan/MyWorks/基础算法入门/example/01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable example01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/example01.dir/build: example01
.PHONY : CMakeFiles/example01.dir/build

CMakeFiles/example01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example01.dir/clean

CMakeFiles/example01.dir/depend:
	cd /home/Evan/MyWorks/基础算法入门/example/01/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Evan/MyWorks/基础算法入门/example/01 /home/Evan/MyWorks/基础算法入门/example/01 /home/Evan/MyWorks/基础算法入门/example/01/build /home/Evan/MyWorks/基础算法入门/example/01/build /home/Evan/MyWorks/基础算法入门/example/01/build/CMakeFiles/example01.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/example01.dir/depend

