# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/isiljic/Downloads/glfw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/isiljic/Desktop/3D/dependencies/glfw

# Include any dependencies generated for this target.
include tests/CMakeFiles/triangle-vulkan.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/triangle-vulkan.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/triangle-vulkan.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/triangle-vulkan.dir/flags.make

tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: tests/CMakeFiles/triangle-vulkan.dir/flags.make
tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: /home/isiljic/Downloads/glfw/tests/triangle-vulkan.c
tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: tests/CMakeFiles/triangle-vulkan.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/isiljic/Desktop/3D/dependencies/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o"
	cd /home/isiljic/Desktop/3D/dependencies/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o -MF CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o.d -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o -c /home/isiljic/Downloads/glfw/tests/triangle-vulkan.c

tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i"
	cd /home/isiljic/Desktop/3D/dependencies/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/isiljic/Downloads/glfw/tests/triangle-vulkan.c > CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i

tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s"
	cd /home/isiljic/Desktop/3D/dependencies/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/isiljic/Downloads/glfw/tests/triangle-vulkan.c -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s

# Object files for target triangle-vulkan
triangle__vulkan_OBJECTS = \
"CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o"

# External object files for target triangle-vulkan
triangle__vulkan_EXTERNAL_OBJECTS =

tests/triangle-vulkan: tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o
tests/triangle-vulkan: tests/CMakeFiles/triangle-vulkan.dir/build.make
tests/triangle-vulkan: src/libglfw3.a
tests/triangle-vulkan: /usr/lib64/libm.so
tests/triangle-vulkan: /usr/lib64/librt.a
tests/triangle-vulkan: /usr/lib64/libm.so
tests/triangle-vulkan: tests/CMakeFiles/triangle-vulkan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/isiljic/Desktop/3D/dependencies/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable triangle-vulkan"
	cd /home/isiljic/Desktop/3D/dependencies/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangle-vulkan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/triangle-vulkan.dir/build: tests/triangle-vulkan
.PHONY : tests/CMakeFiles/triangle-vulkan.dir/build

tests/CMakeFiles/triangle-vulkan.dir/clean:
	cd /home/isiljic/Desktop/3D/dependencies/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/triangle-vulkan.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/triangle-vulkan.dir/clean

tests/CMakeFiles/triangle-vulkan.dir/depend:
	cd /home/isiljic/Desktop/3D/dependencies/glfw && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/isiljic/Downloads/glfw /home/isiljic/Downloads/glfw/tests /home/isiljic/Desktop/3D/dependencies/glfw /home/isiljic/Desktop/3D/dependencies/glfw/tests /home/isiljic/Desktop/3D/dependencies/glfw/tests/CMakeFiles/triangle-vulkan.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/triangle-vulkan.dir/depend

