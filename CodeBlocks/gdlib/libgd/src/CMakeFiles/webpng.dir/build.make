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
include src/CMakeFiles/webpng.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/webpng.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/webpng.dir/flags.make

src/CMakeFiles/webpng.dir/webpng.c.o: src/CMakeFiles/webpng.dir/flags.make
src/CMakeFiles/webpng.dir/webpng.c.o: src/webpng.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/webpng.dir/webpng.c.o"
	cd /home/limjh/src/gdlib/libgd/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/webpng.dir/webpng.c.o   -c /home/limjh/src/gdlib/libgd/src/webpng.c

src/CMakeFiles/webpng.dir/webpng.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/webpng.dir/webpng.c.i"
	cd /home/limjh/src/gdlib/libgd/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/limjh/src/gdlib/libgd/src/webpng.c > CMakeFiles/webpng.dir/webpng.c.i

src/CMakeFiles/webpng.dir/webpng.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/webpng.dir/webpng.c.s"
	cd /home/limjh/src/gdlib/libgd/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/limjh/src/gdlib/libgd/src/webpng.c -o CMakeFiles/webpng.dir/webpng.c.s

src/CMakeFiles/webpng.dir/webpng.c.o.requires:
.PHONY : src/CMakeFiles/webpng.dir/webpng.c.o.requires

src/CMakeFiles/webpng.dir/webpng.c.o.provides: src/CMakeFiles/webpng.dir/webpng.c.o.requires
	$(MAKE) -f src/CMakeFiles/webpng.dir/build.make src/CMakeFiles/webpng.dir/webpng.c.o.provides.build
.PHONY : src/CMakeFiles/webpng.dir/webpng.c.o.provides

src/CMakeFiles/webpng.dir/webpng.c.o.provides.build: src/CMakeFiles/webpng.dir/webpng.c.o

# Object files for target webpng
webpng_OBJECTS = \
"CMakeFiles/webpng.dir/webpng.c.o"

# External object files for target webpng
webpng_EXTERNAL_OBJECTS =

src/webpng: src/CMakeFiles/webpng.dir/webpng.c.o
src/webpng: src/libgd.so
src/webpng: /usr/lib/i386-linux-gnu/libfreetype.so
src/webpng: /usr/lib/i386-linux-gnu/libpng.so
src/webpng: /usr/lib/i386-linux-gnu/libz.so
src/webpng: libimagequant/libimagequant.a
src/webpng: /usr/lib/i386-linux-gnu/libfontconfig.so
src/webpng: src/CMakeFiles/webpng.dir/build.make
src/webpng: src/CMakeFiles/webpng.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable webpng"
	cd /home/limjh/src/gdlib/libgd/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/webpng.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/webpng.dir/build: src/webpng
.PHONY : src/CMakeFiles/webpng.dir/build

src/CMakeFiles/webpng.dir/requires: src/CMakeFiles/webpng.dir/webpng.c.o.requires
.PHONY : src/CMakeFiles/webpng.dir/requires

src/CMakeFiles/webpng.dir/clean:
	cd /home/limjh/src/gdlib/libgd/src && $(CMAKE_COMMAND) -P CMakeFiles/webpng.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/webpng.dir/clean

src/CMakeFiles/webpng.dir/depend:
	cd /home/limjh/src/gdlib/libgd && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd/src /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd/src /home/limjh/src/gdlib/libgd/src/CMakeFiles/webpng.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/webpng.dir/depend

