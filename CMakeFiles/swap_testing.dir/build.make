# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = /home/ag6154lk/KISA_LOP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ag6154lk/KISA_LOP

# Include any dependencies generated for this target.
include CMakeFiles/swap_testing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/swap_testing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/swap_testing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/swap_testing.dir/flags.make

CMakeFiles/swap_testing.dir/codegen:
.PHONY : CMakeFiles/swap_testing.dir/codegen

CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.o: CMakeFiles/swap_testing.dir/flags.make
CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.o: src/GA_testing/Mutation/swap_testing.cpp
CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.o: CMakeFiles/swap_testing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ag6154lk/KISA_LOP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.o -MF CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.o.d -o CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.o -c /home/ag6154lk/KISA_LOP/src/GA_testing/Mutation/swap_testing.cpp

CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ag6154lk/KISA_LOP/src/GA_testing/Mutation/swap_testing.cpp > CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.i

CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ag6154lk/KISA_LOP/src/GA_testing/Mutation/swap_testing.cpp -o CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.s

CMakeFiles/swap_testing.dir/src/GA/GA.cpp.o: CMakeFiles/swap_testing.dir/flags.make
CMakeFiles/swap_testing.dir/src/GA/GA.cpp.o: src/GA/GA.cpp
CMakeFiles/swap_testing.dir/src/GA/GA.cpp.o: CMakeFiles/swap_testing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ag6154lk/KISA_LOP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/swap_testing.dir/src/GA/GA.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/swap_testing.dir/src/GA/GA.cpp.o -MF CMakeFiles/swap_testing.dir/src/GA/GA.cpp.o.d -o CMakeFiles/swap_testing.dir/src/GA/GA.cpp.o -c /home/ag6154lk/KISA_LOP/src/GA/GA.cpp

CMakeFiles/swap_testing.dir/src/GA/GA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/swap_testing.dir/src/GA/GA.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ag6154lk/KISA_LOP/src/GA/GA.cpp > CMakeFiles/swap_testing.dir/src/GA/GA.cpp.i

CMakeFiles/swap_testing.dir/src/GA/GA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/swap_testing.dir/src/GA/GA.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ag6154lk/KISA_LOP/src/GA/GA.cpp -o CMakeFiles/swap_testing.dir/src/GA/GA.cpp.s

CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.o: CMakeFiles/swap_testing.dir/flags.make
CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.o: src/GA/crossover.cpp
CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.o: CMakeFiles/swap_testing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ag6154lk/KISA_LOP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.o -MF CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.o.d -o CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.o -c /home/ag6154lk/KISA_LOP/src/GA/crossover.cpp

CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ag6154lk/KISA_LOP/src/GA/crossover.cpp > CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.i

CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ag6154lk/KISA_LOP/src/GA/crossover.cpp -o CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.s

CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.o: CMakeFiles/swap_testing.dir/flags.make
CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.o: src/GA/mutation.cpp
CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.o: CMakeFiles/swap_testing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ag6154lk/KISA_LOP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.o -MF CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.o.d -o CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.o -c /home/ag6154lk/KISA_LOP/src/GA/mutation.cpp

CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ag6154lk/KISA_LOP/src/GA/mutation.cpp > CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.i

CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ag6154lk/KISA_LOP/src/GA/mutation.cpp -o CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.s

CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.o: CMakeFiles/swap_testing.dir/flags.make
CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.o: src/GA/parent_selection.cpp
CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.o: CMakeFiles/swap_testing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ag6154lk/KISA_LOP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.o -MF CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.o.d -o CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.o -c /home/ag6154lk/KISA_LOP/src/GA/parent_selection.cpp

CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ag6154lk/KISA_LOP/src/GA/parent_selection.cpp > CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.i

CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ag6154lk/KISA_LOP/src/GA/parent_selection.cpp -o CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.s

CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.o: CMakeFiles/swap_testing.dir/flags.make
CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.o: src/GA/population_selection.cpp
CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.o: CMakeFiles/swap_testing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ag6154lk/KISA_LOP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.o -MF CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.o.d -o CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.o -c /home/ag6154lk/KISA_LOP/src/GA/population_selection.cpp

CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ag6154lk/KISA_LOP/src/GA/population_selection.cpp > CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.i

CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ag6154lk/KISA_LOP/src/GA/population_selection.cpp -o CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.s

CMakeFiles/swap_testing.dir/src/IO.cpp.o: CMakeFiles/swap_testing.dir/flags.make
CMakeFiles/swap_testing.dir/src/IO.cpp.o: src/IO.cpp
CMakeFiles/swap_testing.dir/src/IO.cpp.o: CMakeFiles/swap_testing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ag6154lk/KISA_LOP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/swap_testing.dir/src/IO.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/swap_testing.dir/src/IO.cpp.o -MF CMakeFiles/swap_testing.dir/src/IO.cpp.o.d -o CMakeFiles/swap_testing.dir/src/IO.cpp.o -c /home/ag6154lk/KISA_LOP/src/IO.cpp

CMakeFiles/swap_testing.dir/src/IO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/swap_testing.dir/src/IO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ag6154lk/KISA_LOP/src/IO.cpp > CMakeFiles/swap_testing.dir/src/IO.cpp.i

CMakeFiles/swap_testing.dir/src/IO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/swap_testing.dir/src/IO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ag6154lk/KISA_LOP/src/IO.cpp -o CMakeFiles/swap_testing.dir/src/IO.cpp.s

CMakeFiles/swap_testing.dir/src/LOP.cpp.o: CMakeFiles/swap_testing.dir/flags.make
CMakeFiles/swap_testing.dir/src/LOP.cpp.o: src/LOP.cpp
CMakeFiles/swap_testing.dir/src/LOP.cpp.o: CMakeFiles/swap_testing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ag6154lk/KISA_LOP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/swap_testing.dir/src/LOP.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/swap_testing.dir/src/LOP.cpp.o -MF CMakeFiles/swap_testing.dir/src/LOP.cpp.o.d -o CMakeFiles/swap_testing.dir/src/LOP.cpp.o -c /home/ag6154lk/KISA_LOP/src/LOP.cpp

CMakeFiles/swap_testing.dir/src/LOP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/swap_testing.dir/src/LOP.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ag6154lk/KISA_LOP/src/LOP.cpp > CMakeFiles/swap_testing.dir/src/LOP.cpp.i

CMakeFiles/swap_testing.dir/src/LOP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/swap_testing.dir/src/LOP.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ag6154lk/KISA_LOP/src/LOP.cpp -o CMakeFiles/swap_testing.dir/src/LOP.cpp.s

CMakeFiles/swap_testing.dir/src/memory.cpp.o: CMakeFiles/swap_testing.dir/flags.make
CMakeFiles/swap_testing.dir/src/memory.cpp.o: src/memory.cpp
CMakeFiles/swap_testing.dir/src/memory.cpp.o: CMakeFiles/swap_testing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ag6154lk/KISA_LOP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/swap_testing.dir/src/memory.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/swap_testing.dir/src/memory.cpp.o -MF CMakeFiles/swap_testing.dir/src/memory.cpp.o.d -o CMakeFiles/swap_testing.dir/src/memory.cpp.o -c /home/ag6154lk/KISA_LOP/src/memory.cpp

CMakeFiles/swap_testing.dir/src/memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/swap_testing.dir/src/memory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ag6154lk/KISA_LOP/src/memory.cpp > CMakeFiles/swap_testing.dir/src/memory.cpp.i

CMakeFiles/swap_testing.dir/src/memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/swap_testing.dir/src/memory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ag6154lk/KISA_LOP/src/memory.cpp -o CMakeFiles/swap_testing.dir/src/memory.cpp.s

# Object files for target swap_testing
swap_testing_OBJECTS = \
"CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.o" \
"CMakeFiles/swap_testing.dir/src/GA/GA.cpp.o" \
"CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.o" \
"CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.o" \
"CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.o" \
"CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.o" \
"CMakeFiles/swap_testing.dir/src/IO.cpp.o" \
"CMakeFiles/swap_testing.dir/src/LOP.cpp.o" \
"CMakeFiles/swap_testing.dir/src/memory.cpp.o"

# External object files for target swap_testing
swap_testing_EXTERNAL_OBJECTS =

build/tests/swap_testing: CMakeFiles/swap_testing.dir/src/GA_testing/Mutation/swap_testing.cpp.o
build/tests/swap_testing: CMakeFiles/swap_testing.dir/src/GA/GA.cpp.o
build/tests/swap_testing: CMakeFiles/swap_testing.dir/src/GA/crossover.cpp.o
build/tests/swap_testing: CMakeFiles/swap_testing.dir/src/GA/mutation.cpp.o
build/tests/swap_testing: CMakeFiles/swap_testing.dir/src/GA/parent_selection.cpp.o
build/tests/swap_testing: CMakeFiles/swap_testing.dir/src/GA/population_selection.cpp.o
build/tests/swap_testing: CMakeFiles/swap_testing.dir/src/IO.cpp.o
build/tests/swap_testing: CMakeFiles/swap_testing.dir/src/LOP.cpp.o
build/tests/swap_testing: CMakeFiles/swap_testing.dir/src/memory.cpp.o
build/tests/swap_testing: CMakeFiles/swap_testing.dir/build.make
build/tests/swap_testing: CMakeFiles/swap_testing.dir/compiler_depend.ts
build/tests/swap_testing: CMakeFiles/swap_testing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ag6154lk/KISA_LOP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable build/tests/swap_testing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/swap_testing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/swap_testing.dir/build: build/tests/swap_testing
.PHONY : CMakeFiles/swap_testing.dir/build

CMakeFiles/swap_testing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/swap_testing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/swap_testing.dir/clean

CMakeFiles/swap_testing.dir/depend:
	cd /home/ag6154lk/KISA_LOP && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ag6154lk/KISA_LOP /home/ag6154lk/KISA_LOP /home/ag6154lk/KISA_LOP /home/ag6154lk/KISA_LOP /home/ag6154lk/KISA_LOP/CMakeFiles/swap_testing.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/swap_testing.dir/depend

