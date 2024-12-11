# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/giovanni/Desktop/sci-toolbox-final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/giovanni/Desktop/sci-toolbox-final/build

# Include any dependencies generated for this target.
include apps/CMakeFiles/interpol_app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include apps/CMakeFiles/interpol_app.dir/compiler_depend.make

# Include the progress variables for this target.
include apps/CMakeFiles/interpol_app.dir/progress.make

# Include the compile flags for this target's objects.
include apps/CMakeFiles/interpol_app.dir/flags.make

apps/CMakeFiles/interpol_app.dir/interpol_app.cpp.o: apps/CMakeFiles/interpol_app.dir/flags.make
apps/CMakeFiles/interpol_app.dir/interpol_app.cpp.o: /home/giovanni/Desktop/sci-toolbox-final/apps/interpol_app.cpp
apps/CMakeFiles/interpol_app.dir/interpol_app.cpp.o: apps/CMakeFiles/interpol_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/giovanni/Desktop/sci-toolbox-final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object apps/CMakeFiles/interpol_app.dir/interpol_app.cpp.o"
	cd /home/giovanni/Desktop/sci-toolbox-final/build/apps && /usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT apps/CMakeFiles/interpol_app.dir/interpol_app.cpp.o -MF CMakeFiles/interpol_app.dir/interpol_app.cpp.o.d -o CMakeFiles/interpol_app.dir/interpol_app.cpp.o -c /home/giovanni/Desktop/sci-toolbox-final/apps/interpol_app.cpp

apps/CMakeFiles/interpol_app.dir/interpol_app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/interpol_app.dir/interpol_app.cpp.i"
	cd /home/giovanni/Desktop/sci-toolbox-final/build/apps && /usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/giovanni/Desktop/sci-toolbox-final/apps/interpol_app.cpp > CMakeFiles/interpol_app.dir/interpol_app.cpp.i

apps/CMakeFiles/interpol_app.dir/interpol_app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/interpol_app.dir/interpol_app.cpp.s"
	cd /home/giovanni/Desktop/sci-toolbox-final/build/apps && /usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/giovanni/Desktop/sci-toolbox-final/apps/interpol_app.cpp -o CMakeFiles/interpol_app.dir/interpol_app.cpp.s

# Object files for target interpol_app
interpol_app_OBJECTS = \
"CMakeFiles/interpol_app.dir/interpol_app.cpp.o"

# External object files for target interpol_app
interpol_app_EXTERNAL_OBJECTS =

apps/interpol_app: apps/CMakeFiles/interpol_app.dir/interpol_app.cpp.o
apps/interpol_app: apps/CMakeFiles/interpol_app.dir/build.make
apps/interpol_app: src/libinterpolation.so
apps/interpol_app: /usr/local/lib/libboost_json.so.1.86.0
apps/interpol_app: /usr/local/lib/libboost_container.so.1.86.0
apps/interpol_app: /usr/local/lib/libboost_system.so.1.86.0
apps/interpol_app: /usr/local/lib/libboost_filesystem.so.1.86.0
apps/interpol_app: /usr/local/lib/libboost_atomic.so.1.86.0
apps/interpol_app: /usr/lib/x86_64-linux-gnu/libgsl.so
apps/interpol_app: /usr/lib/x86_64-linux-gnu/libgslcblas.so
apps/interpol_app: apps/CMakeFiles/interpol_app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/giovanni/Desktop/sci-toolbox-final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable interpol_app"
	cd /home/giovanni/Desktop/sci-toolbox-final/build/apps && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interpol_app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/CMakeFiles/interpol_app.dir/build: apps/interpol_app
.PHONY : apps/CMakeFiles/interpol_app.dir/build

apps/CMakeFiles/interpol_app.dir/clean:
	cd /home/giovanni/Desktop/sci-toolbox-final/build/apps && $(CMAKE_COMMAND) -P CMakeFiles/interpol_app.dir/cmake_clean.cmake
.PHONY : apps/CMakeFiles/interpol_app.dir/clean

apps/CMakeFiles/interpol_app.dir/depend:
	cd /home/giovanni/Desktop/sci-toolbox-final/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/giovanni/Desktop/sci-toolbox-final /home/giovanni/Desktop/sci-toolbox-final/apps /home/giovanni/Desktop/sci-toolbox-final/build /home/giovanni/Desktop/sci-toolbox-final/build/apps /home/giovanni/Desktop/sci-toolbox-final/build/apps/CMakeFiles/interpol_app.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : apps/CMakeFiles/interpol_app.dir/depend

