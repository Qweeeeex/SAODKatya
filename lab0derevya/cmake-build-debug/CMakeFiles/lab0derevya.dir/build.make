# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = Q:\SAOD\lab0derevya

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = Q:\SAOD\lab0derevya\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab0derevya.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab0derevya.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab0derevya.dir/flags.make

CMakeFiles/lab0derevya.dir/main.cpp.obj: CMakeFiles/lab0derevya.dir/flags.make
CMakeFiles/lab0derevya.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=Q:\SAOD\lab0derevya\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab0derevya.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\lab0derevya.dir\main.cpp.obj -c Q:\SAOD\lab0derevya\main.cpp

CMakeFiles/lab0derevya.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab0derevya.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E Q:\SAOD\lab0derevya\main.cpp > CMakeFiles\lab0derevya.dir\main.cpp.i

CMakeFiles/lab0derevya.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab0derevya.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S Q:\SAOD\lab0derevya\main.cpp -o CMakeFiles\lab0derevya.dir\main.cpp.s

# Object files for target lab0derevya
lab0derevya_OBJECTS = \
"CMakeFiles/lab0derevya.dir/main.cpp.obj"

# External object files for target lab0derevya
lab0derevya_EXTERNAL_OBJECTS =

lab0derevya.exe: CMakeFiles/lab0derevya.dir/main.cpp.obj
lab0derevya.exe: CMakeFiles/lab0derevya.dir/build.make
lab0derevya.exe: CMakeFiles/lab0derevya.dir/linklibs.rsp
lab0derevya.exe: CMakeFiles/lab0derevya.dir/objects1.rsp
lab0derevya.exe: CMakeFiles/lab0derevya.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=Q:\SAOD\lab0derevya\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab0derevya.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lab0derevya.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab0derevya.dir/build: lab0derevya.exe

.PHONY : CMakeFiles/lab0derevya.dir/build

CMakeFiles/lab0derevya.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lab0derevya.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lab0derevya.dir/clean

CMakeFiles/lab0derevya.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" Q:\SAOD\lab0derevya Q:\SAOD\lab0derevya Q:\SAOD\lab0derevya\cmake-build-debug Q:\SAOD\lab0derevya\cmake-build-debug Q:\SAOD\lab0derevya\cmake-build-debug\CMakeFiles\lab0derevya.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab0derevya.dir/depend

