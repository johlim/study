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
include src/CMakeFiles/annotate.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/annotate.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/annotate.dir/flags.make

src/CMakeFiles/annotate.dir/annotate.c.o: src/CMakeFiles/annotate.dir/flags.make
src/CMakeFiles/annotate.dir/annotate.c.o: src/annotate.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/annotate.dir/annotate.c.o"
	cd /home/limjh/src/gdlib/libgd/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/annotate.dir/annotate.c.o   -c /home/limjh/src/gdlib/libgd/src/annotate.c

src/CMakeFiles/annotate.dir/annotate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/annotate.dir/annotate.c.i"
	cd /home/limjh/src/gdlib/libgd/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/limjh/src/gdlib/libgd/src/annotate.c > CMakeFiles/annotate.dir/annotate.c.i

src/CMakeFiles/annotate.dir/annotate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/annotate.dir/annotate.c.s"
	cd /home/limjh/src/gdlib/libgd/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/limjh/src/gdlib/libgd/src/annotate.c -o CMakeFiles/annotate.dir/annotate.c.s

src/CMakeFiles/annotate.dir/annotate.c.o.requires:
.PHONY : src/CMakeFiles/annotate.dir/annotate.c.o.requires

src/CMakeFiles/annotate.dir/annotate.c.o.provides: src/CMakeFiles/annotate.dir/annotate.c.o.requires
	$(MAKE) -f src/CMakeFiles/annotate.dir/build.make src/CMakeFiles/annotate.dir/annotate.c.o.provides.build
.PHONY : src/CMakeFiles/annotate.dir/annotate.c.o.provides

src/CMakeFiles/annotate.dir/annotate.c.o.provides.build: src/CMakeFiles/annotate.dir/annotate.c.o

# Object files for target annotate
annotate_OBJECTS = \
"CMakeFiles/annotate.dir/annotate.c.o"

# External object files for target annotate
annotate_EXTERNAL_OBJECTS =

src/annotate: src/CMakeFiles/annotate.dir/annotate.c.o
src/annotate: src/libgd.so
src/annotate: /usr/lib/i386-linux-gnu/libfreetype.so
src/annotate: /usr/lib/i386-linux-gnu/libpng.so
src/annotate: /usr/lib/i386-linux-gnu/libz.so
src/annotate: libimagequant/libimagequant.a
src/annotate: /usr/lib/i386-linux-gnu/libfontconfig.so
src/annotate: src/CMakeFiles/annotate.dir/build.make
src/annotate: src/CMakeFiles/annotate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable annotate"
	cd /home/limjh/src/gdlib/libgd/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/annotate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/annotate.dir/build: src/annotate
.PHONY : src/CMakeFiles/annotate.dir/build

src/CMakeFiles/annotate.dir/requires: src/CMakeFiles/annotate.dir/annotate.c.o.requires
.PHONY : src/CMakeFiles/annotate.dir/requires

src/CMakeFiles/annotate.dir/clean:
	cd /home/limjh/src/gdlib/libgd/src && $(CMAKE_COMMAND) -P CMakeFiles/annotate.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/annotate.dir/clean

src/CMakeFiles/annotate.dir/depend:
	cd /home/limjh/src/gdlib/libgd && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd/src /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd/src /home/limjh/src/gdlib/libgd/src/CMakeFiles/annotate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/annotate.dir/depend

