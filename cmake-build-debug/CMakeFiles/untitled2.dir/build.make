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
CMAKE_COMMAND = /home/eran/softwares/clion-2019.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/eran/softwares/clion-2019.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/eran/CLionProjects/tau_swp_pca

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eran/CLionProjects/tau_swp_pca/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/untitled2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled2.dir/flags.make

CMakeFiles/untitled2.dir/cov.c.o: CMakeFiles/untitled2.dir/flags.make
CMakeFiles/untitled2.dir/cov.c.o: ../cov.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eran/CLionProjects/tau_swp_pca/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/untitled2.dir/cov.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/untitled2.dir/cov.c.o   -c /home/eran/CLionProjects/tau_swp_pca/cov.c

CMakeFiles/untitled2.dir/cov.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/untitled2.dir/cov.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eran/CLionProjects/tau_swp_pca/cov.c > CMakeFiles/untitled2.dir/cov.c.i

CMakeFiles/untitled2.dir/cov.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/untitled2.dir/cov.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eran/CLionProjects/tau_swp_pca/cov.c -o CMakeFiles/untitled2.dir/cov.c.s

CMakeFiles/untitled2.dir/eigen.c.o: CMakeFiles/untitled2.dir/flags.make
CMakeFiles/untitled2.dir/eigen.c.o: ../eigen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eran/CLionProjects/tau_swp_pca/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/untitled2.dir/eigen.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/untitled2.dir/eigen.c.o   -c /home/eran/CLionProjects/tau_swp_pca/eigen.c

CMakeFiles/untitled2.dir/eigen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/untitled2.dir/eigen.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eran/CLionProjects/tau_swp_pca/eigen.c > CMakeFiles/untitled2.dir/eigen.c.i

CMakeFiles/untitled2.dir/eigen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/untitled2.dir/eigen.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eran/CLionProjects/tau_swp_pca/eigen.c -o CMakeFiles/untitled2.dir/eigen.c.s

# Object files for target untitled2
untitled2_OBJECTS = \
"CMakeFiles/untitled2.dir/cov.c.o" \
"CMakeFiles/untitled2.dir/eigen.c.o"

# External object files for target untitled2
untitled2_EXTERNAL_OBJECTS =

untitled2: CMakeFiles/untitled2.dir/cov.c.o
untitled2: CMakeFiles/untitled2.dir/eigen.c.o
untitled2: CMakeFiles/untitled2.dir/build.make
untitled2: CMakeFiles/untitled2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eran/CLionProjects/tau_swp_pca/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable untitled2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled2.dir/build: untitled2

.PHONY : CMakeFiles/untitled2.dir/build

CMakeFiles/untitled2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled2.dir/clean

CMakeFiles/untitled2.dir/depend:
	cd /home/eran/CLionProjects/tau_swp_pca/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eran/CLionProjects/tau_swp_pca /home/eran/CLionProjects/tau_swp_pca /home/eran/CLionProjects/tau_swp_pca/cmake-build-debug /home/eran/CLionProjects/tau_swp_pca/cmake-build-debug /home/eran/CLionProjects/tau_swp_pca/cmake-build-debug/CMakeFiles/untitled2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/untitled2.dir/depend

