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
include src/CMakeFiles/gd2togif.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/gd2togif.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/gd2togif.dir/flags.make

src/CMakeFiles/gd2togif.dir/gd2togif.c.o: src/CMakeFiles/gd2togif.dir/flags.make
src/CMakeFiles/gd2togif.dir/gd2togif.c.o: src/gd2togif.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/gd2togif.dir/gd2togif.c.o"
	cd /home/limjh/src/gdlib/libgd/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/gd2togif.dir/gd2togif.c.o   -c /home/limjh/src/gdlib/libgd/src/gd2togif.c

src/CMakeFiles/gd2togif.dir/gd2togif.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gd2togif.dir/gd2togif.c.i"
	cd /home/limjh/src/gdlib/libgd/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/limjh/src/gdlib/libgd/src/gd2togif.c > CMakeFiles/gd2togif.dir/gd2togif.c.i

src/CMakeFiles/gd2togif.dir/gd2togif.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gd2togif.dir/gd2togif.c.s"
	cd /home/limjh/src/gdlib/libgd/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/limjh/src/gdlib/libgd/src/gd2togif.c -o CMakeFiles/gd2togif.dir/gd2togif.c.s

src/CMakeFiles/gd2togif.dir/gd2togif.c.o.requires:
.PHONY : src/CMakeFiles/gd2togif.dir/gd2togif.c.o.requires

src/CMakeFiles/gd2togif.dir/gd2togif.c.o.provides: src/CMakeFiles/gd2togif.dir/gd2togif.c.o.requires
	$(MAKE) -f src/CMakeFiles/gd2togif.dir/build.make src/CMakeFiles/gd2togif.dir/gd2togif.c.o.provides.build
.PHONY : src/CMakeFiles/gd2togif.dir/gd2togif.c.o.provides

src/CMakeFiles/gd2togif.dir/gd2togif.c.o.provides.build: src/CMakeFiles/gd2togif.dir/gd2togif.c.o

# Object files for target gd2togif
gd2togif_OBJECTS = \
"CMakeFiles/gd2togif.dir/gd2togif.c.o"

# External object files for target gd2togif
gd2togif_EXTERNAL_OBJECTS =

src/gd2togif: src/CMakeFiles/gd2togif.dir/gd2togif.c.o
src/gd2togif: src/libgd.so
src/gd2togif: /usr/lib/i386-linux-gnu/libfreetype.so
src/gd2togif: /usr/lib/i386-linux-gnu/libpng.so
src/gd2togif: /usr/lib/i386-linux-gnu/libz.so
src/gd2togif: libimagequant/libimagequant.a
src/gd2togif: /usr/lib/i386-linux-gnu/libfontconfig.so
src/gd2togif: src/CMakeFiles/gd2togif.dir/build.make
src/gd2togif: src/CMakeFiles/gd2togif.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable gd2togif"
	cd /home/limjh/src/gdlib/libgd/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gd2togif.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/gd2togif.dir/build: src/gd2togif
.PHONY : src/CMakeFiles/gd2togif.dir/build

src/CMakeFiles/gd2togif.dir/requires: src/CMakeFiles/gd2togif.dir/gd2togif.c.o.requires
.PHONY : src/CMakeFiles/gd2togif.dir/requires

src/CMakeFiles/gd2togif.dir/clean:
	cd /home/limjh/src/gdlib/libgd/src && $(CMAKE_COMMAND) -P CMakeFiles/gd2togif.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/gd2togif.dir/clean

src/CMakeFiles/gd2togif.dir/depend:
	cd /home/limjh/src/gdlib/libgd && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd/src /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd/src /home/limjh/src/gdlib/libgd/src/CMakeFiles/gd2togif.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/gd2togif.dir/depend

