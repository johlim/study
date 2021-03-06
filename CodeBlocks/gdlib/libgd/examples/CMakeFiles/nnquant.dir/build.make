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
CMAKE_SOURCE_DIR = /home/limjh/src/gdlib/libgd

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/limjh/src/gdlib/libgd

# Include any dependencies generated for this target.
include examples/CMakeFiles/nnquant.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/nnquant.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/nnquant.dir/flags.make

examples/CMakeFiles/nnquant.dir/nnquant.c.o: examples/CMakeFiles/nnquant.dir/flags.make
examples/CMakeFiles/nnquant.dir/nnquant.c.o: examples/nnquant.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/nnquant.dir/nnquant.c.o"
	cd /home/limjh/src/gdlib/libgd/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/nnquant.dir/nnquant.c.o   -c /home/limjh/src/gdlib/libgd/examples/nnquant.c

examples/CMakeFiles/nnquant.dir/nnquant.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nnquant.dir/nnquant.c.i"
	cd /home/limjh/src/gdlib/libgd/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/limjh/src/gdlib/libgd/examples/nnquant.c > CMakeFiles/nnquant.dir/nnquant.c.i

examples/CMakeFiles/nnquant.dir/nnquant.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nnquant.dir/nnquant.c.s"
	cd /home/limjh/src/gdlib/libgd/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/limjh/src/gdlib/libgd/examples/nnquant.c -o CMakeFiles/nnquant.dir/nnquant.c.s

examples/CMakeFiles/nnquant.dir/nnquant.c.o.requires:
.PHONY : examples/CMakeFiles/nnquant.dir/nnquant.c.o.requires

examples/CMakeFiles/nnquant.dir/nnquant.c.o.provides: examples/CMakeFiles/nnquant.dir/nnquant.c.o.requires
	$(MAKE) -f examples/CMakeFiles/nnquant.dir/build.make examples/CMakeFiles/nnquant.dir/nnquant.c.o.provides.build
.PHONY : examples/CMakeFiles/nnquant.dir/nnquant.c.o.provides

examples/CMakeFiles/nnquant.dir/nnquant.c.o.provides.build: examples/CMakeFiles/nnquant.dir/nnquant.c.o

# Object files for target nnquant
nnquant_OBJECTS = \
"CMakeFiles/nnquant.dir/nnquant.c.o"

# External object files for target nnquant
nnquant_EXTERNAL_OBJECTS =

examples/nnquant: examples/CMakeFiles/nnquant.dir/nnquant.c.o
examples/nnquant: src/libgd.so
examples/nnquant: /usr/lib/i386-linux-gnu/libfreetype.so
examples/nnquant: /usr/lib/i386-linux-gnu/libpng.so
examples/nnquant: /usr/lib/i386-linux-gnu/libz.so
examples/nnquant: libimagequant/libimagequant.a
examples/nnquant: /usr/lib/i386-linux-gnu/libfontconfig.so
examples/nnquant: examples/CMakeFiles/nnquant.dir/build.make
examples/nnquant: examples/CMakeFiles/nnquant.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable nnquant"
	cd /home/limjh/src/gdlib/libgd/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nnquant.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/nnquant.dir/build: examples/nnquant
.PHONY : examples/CMakeFiles/nnquant.dir/build

examples/CMakeFiles/nnquant.dir/requires: examples/CMakeFiles/nnquant.dir/nnquant.c.o.requires
.PHONY : examples/CMakeFiles/nnquant.dir/requires

examples/CMakeFiles/nnquant.dir/clean:
	cd /home/limjh/src/gdlib/libgd/examples && $(CMAKE_COMMAND) -P CMakeFiles/nnquant.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/nnquant.dir/clean

examples/CMakeFiles/nnquant.dir/depend:
	cd /home/limjh/src/gdlib/libgd && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd/examples /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd/examples /home/limjh/src/gdlib/libgd/examples/CMakeFiles/nnquant.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/nnquant.dir/depend

