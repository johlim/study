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
include examples/CMakeFiles/arc.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/arc.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/arc.dir/flags.make

examples/CMakeFiles/arc.dir/arc.c.o: examples/CMakeFiles/arc.dir/flags.make
examples/CMakeFiles/arc.dir/arc.c.o: examples/arc.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/arc.dir/arc.c.o"
	cd /home/limjh/src/gdlib/libgd/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/arc.dir/arc.c.o   -c /home/limjh/src/gdlib/libgd/examples/arc.c

examples/CMakeFiles/arc.dir/arc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/arc.dir/arc.c.i"
	cd /home/limjh/src/gdlib/libgd/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/limjh/src/gdlib/libgd/examples/arc.c > CMakeFiles/arc.dir/arc.c.i

examples/CMakeFiles/arc.dir/arc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/arc.dir/arc.c.s"
	cd /home/limjh/src/gdlib/libgd/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/limjh/src/gdlib/libgd/examples/arc.c -o CMakeFiles/arc.dir/arc.c.s

examples/CMakeFiles/arc.dir/arc.c.o.requires:
.PHONY : examples/CMakeFiles/arc.dir/arc.c.o.requires

examples/CMakeFiles/arc.dir/arc.c.o.provides: examples/CMakeFiles/arc.dir/arc.c.o.requires
	$(MAKE) -f examples/CMakeFiles/arc.dir/build.make examples/CMakeFiles/arc.dir/arc.c.o.provides.build
.PHONY : examples/CMakeFiles/arc.dir/arc.c.o.provides

examples/CMakeFiles/arc.dir/arc.c.o.provides.build: examples/CMakeFiles/arc.dir/arc.c.o

# Object files for target arc
arc_OBJECTS = \
"CMakeFiles/arc.dir/arc.c.o"

# External object files for target arc
arc_EXTERNAL_OBJECTS =

examples/arc: examples/CMakeFiles/arc.dir/arc.c.o
examples/arc: src/libgd.so
examples/arc: /usr/lib/i386-linux-gnu/libfreetype.so
examples/arc: /usr/lib/i386-linux-gnu/libpng.so
examples/arc: /usr/lib/i386-linux-gnu/libz.so
examples/arc: libimagequant/libimagequant.a
examples/arc: /usr/lib/i386-linux-gnu/libfontconfig.so
examples/arc: examples/CMakeFiles/arc.dir/build.make
examples/arc: examples/CMakeFiles/arc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable arc"
	cd /home/limjh/src/gdlib/libgd/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/arc.dir/build: examples/arc
.PHONY : examples/CMakeFiles/arc.dir/build

examples/CMakeFiles/arc.dir/requires: examples/CMakeFiles/arc.dir/arc.c.o.requires
.PHONY : examples/CMakeFiles/arc.dir/requires

examples/CMakeFiles/arc.dir/clean:
	cd /home/limjh/src/gdlib/libgd/examples && $(CMAKE_COMMAND) -P CMakeFiles/arc.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/arc.dir/clean

examples/CMakeFiles/arc.dir/depend:
	cd /home/limjh/src/gdlib/libgd && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd/examples /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd/examples /home/limjh/src/gdlib/libgd/examples/CMakeFiles/arc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/arc.dir/depend

