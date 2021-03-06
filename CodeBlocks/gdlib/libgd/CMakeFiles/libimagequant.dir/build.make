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

# Utility rule file for libimagequant.

# Include the progress variables for this target.
include CMakeFiles/libimagequant.dir/progress.make

CMakeFiles/libimagequant: CMakeFiles/libimagequant-complete

CMakeFiles/libimagequant-complete: libimagequant-prefix/src/libimagequant-stamp/libimagequant-install
CMakeFiles/libimagequant-complete: libimagequant-prefix/src/libimagequant-stamp/libimagequant-mkdir
CMakeFiles/libimagequant-complete: libimagequant-prefix/src/libimagequant-stamp/libimagequant-download
CMakeFiles/libimagequant-complete: libimagequant-prefix/src/libimagequant-stamp/libimagequant-update
CMakeFiles/libimagequant-complete: libimagequant-prefix/src/libimagequant-stamp/libimagequant-patch
CMakeFiles/libimagequant-complete: libimagequant-prefix/src/libimagequant-stamp/libimagequant-configure
CMakeFiles/libimagequant-complete: libimagequant-prefix/src/libimagequant-stamp/libimagequant-build
CMakeFiles/libimagequant-complete: libimagequant-prefix/src/libimagequant-stamp/libimagequant-install
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Completed 'libimagequant'"
	/usr/bin/cmake -E make_directory /home/limjh/src/gdlib/libgd/CMakeFiles
	/usr/bin/cmake -E touch /home/limjh/src/gdlib/libgd/CMakeFiles/libimagequant-complete
	/usr/bin/cmake -E touch /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp/libimagequant-done

libimagequant-prefix/src/libimagequant-stamp/libimagequant-install: libimagequant-prefix/src/libimagequant-stamp/libimagequant-build
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Performing install step for 'libimagequant'"
	cd /home/limjh/src/gdlib/libgd/libimagequant && true
	cd /home/limjh/src/gdlib/libgd/libimagequant && /usr/bin/cmake -E touch /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp/libimagequant-install

libimagequant-prefix/src/libimagequant-stamp/libimagequant-mkdir:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Creating directories for 'libimagequant'"
	/usr/bin/cmake -E make_directory /home/limjh/src/gdlib/libgd/libimagequant
	/usr/bin/cmake -E make_directory /home/limjh/src/gdlib/libgd/libimagequant
	/usr/bin/cmake -E make_directory /home/limjh/src/gdlib/libgd/libimagequant
	/usr/bin/cmake -E make_directory /home/limjh/src/gdlib/libgd/libimagequant-prefix/tmp
	/usr/bin/cmake -E make_directory /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp
	/usr/bin/cmake -E make_directory /home/limjh/src/gdlib/libgd/libimagequant-prefix/src
	/usr/bin/cmake -E touch /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp/libimagequant-mkdir

libimagequant-prefix/src/libimagequant-stamp/libimagequant-download: libimagequant-prefix/src/libimagequant-stamp/libimagequant-urlinfo.txt
libimagequant-prefix/src/libimagequant-stamp/libimagequant-download: libimagequant-prefix/src/libimagequant-stamp/libimagequant-mkdir
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Performing download step (download, verify and extract) for 'libimagequant'"
	/usr/bin/cmake -P /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp/download-libimagequant.cmake
	/usr/bin/cmake -P /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp/verify-libimagequant.cmake /usr/bin/cmake -P /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp/extract-libimagequant.cmake
	/usr/bin/cmake -E touch /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp/libimagequant-download

libimagequant-prefix/src/libimagequant-stamp/libimagequant-update: libimagequant-prefix/src/libimagequant-stamp/libimagequant-download
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "No update step for 'libimagequant'"
	/usr/bin/cmake -E touch /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp/libimagequant-update

libimagequant-prefix/src/libimagequant-stamp/libimagequant-patch: libimagequant-prefix/src/libimagequant-stamp/libimagequant-download
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "No patch step for 'libimagequant'"
	/usr/bin/cmake -E touch /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp/libimagequant-patch

libimagequant-prefix/src/libimagequant-stamp/libimagequant-configure: libimagequant-prefix/tmp/libimagequant-cfgcmd.txt
libimagequant-prefix/src/libimagequant-stamp/libimagequant-configure: libimagequant-prefix/src/libimagequant-stamp/libimagequant-update
libimagequant-prefix/src/libimagequant-stamp/libimagequant-configure: libimagequant-prefix/src/libimagequant-stamp/libimagequant-patch
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Performing configure step for 'libimagequant'"
	cd /home/limjh/src/gdlib/libgd/libimagequant && true
	cd /home/limjh/src/gdlib/libgd/libimagequant && /usr/bin/cmake -E touch /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp/libimagequant-configure

libimagequant-prefix/src/libimagequant-stamp/libimagequant-build: libimagequant-prefix/src/libimagequant-stamp/libimagequant-configure
	$(CMAKE_COMMAND) -E cmake_progress_report /home/limjh/src/gdlib/libgd/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Performing build step for 'libimagequant'"
	cd /home/limjh/src/gdlib/libgd/libimagequant && make static
	cd /home/limjh/src/gdlib/libgd/libimagequant && /usr/bin/cmake -E touch /home/limjh/src/gdlib/libgd/libimagequant-prefix/src/libimagequant-stamp/libimagequant-build

libimagequant: CMakeFiles/libimagequant
libimagequant: CMakeFiles/libimagequant-complete
libimagequant: libimagequant-prefix/src/libimagequant-stamp/libimagequant-install
libimagequant: libimagequant-prefix/src/libimagequant-stamp/libimagequant-mkdir
libimagequant: libimagequant-prefix/src/libimagequant-stamp/libimagequant-download
libimagequant: libimagequant-prefix/src/libimagequant-stamp/libimagequant-update
libimagequant: libimagequant-prefix/src/libimagequant-stamp/libimagequant-patch
libimagequant: libimagequant-prefix/src/libimagequant-stamp/libimagequant-configure
libimagequant: libimagequant-prefix/src/libimagequant-stamp/libimagequant-build
libimagequant: CMakeFiles/libimagequant.dir/build.make
.PHONY : libimagequant

# Rule to build all files generated by this target.
CMakeFiles/libimagequant.dir/build: libimagequant
.PHONY : CMakeFiles/libimagequant.dir/build

CMakeFiles/libimagequant.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libimagequant.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libimagequant.dir/clean

CMakeFiles/libimagequant.dir/depend:
	cd /home/limjh/src/gdlib/libgd && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd /home/limjh/src/gdlib/libgd/CMakeFiles/libimagequant.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libimagequant.dir/depend

