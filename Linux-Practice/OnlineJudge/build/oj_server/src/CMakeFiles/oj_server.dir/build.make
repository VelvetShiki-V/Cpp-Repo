# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shiki/linux_-practice/OnlineJudge

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shiki/linux_-practice/OnlineJudge/build

# Include any dependencies generated for this target.
include oj_server/src/CMakeFiles/oj_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include oj_server/src/CMakeFiles/oj_server.dir/compiler_depend.make

# Include the progress variables for this target.
include oj_server/src/CMakeFiles/oj_server.dir/progress.make

# Include the compile flags for this target's objects.
include oj_server/src/CMakeFiles/oj_server.dir/flags.make

oj_server/src/CMakeFiles/oj_server.dir/oj_server.cc.o: oj_server/src/CMakeFiles/oj_server.dir/flags.make
oj_server/src/CMakeFiles/oj_server.dir/oj_server.cc.o: /home/shiki/linux_-practice/OnlineJudge/oj_server/src/oj_server.cc
oj_server/src/CMakeFiles/oj_server.dir/oj_server.cc.o: oj_server/src/CMakeFiles/oj_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shiki/linux_-practice/OnlineJudge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object oj_server/src/CMakeFiles/oj_server.dir/oj_server.cc.o"
	cd /home/shiki/linux_-practice/OnlineJudge/build/oj_server/src && /opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT oj_server/src/CMakeFiles/oj_server.dir/oj_server.cc.o -MF CMakeFiles/oj_server.dir/oj_server.cc.o.d -o CMakeFiles/oj_server.dir/oj_server.cc.o -c /home/shiki/linux_-practice/OnlineJudge/oj_server/src/oj_server.cc

oj_server/src/CMakeFiles/oj_server.dir/oj_server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oj_server.dir/oj_server.cc.i"
	cd /home/shiki/linux_-practice/OnlineJudge/build/oj_server/src && /opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shiki/linux_-practice/OnlineJudge/oj_server/src/oj_server.cc > CMakeFiles/oj_server.dir/oj_server.cc.i

oj_server/src/CMakeFiles/oj_server.dir/oj_server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oj_server.dir/oj_server.cc.s"
	cd /home/shiki/linux_-practice/OnlineJudge/build/oj_server/src && /opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shiki/linux_-practice/OnlineJudge/oj_server/src/oj_server.cc -o CMakeFiles/oj_server.dir/oj_server.cc.s

# Object files for target oj_server
oj_server_OBJECTS = \
"CMakeFiles/oj_server.dir/oj_server.cc.o"

# External object files for target oj_server
oj_server_EXTERNAL_OBJECTS =

/home/shiki/linux_-practice/OnlineJudge/bin/oj_server: oj_server/src/CMakeFiles/oj_server.dir/oj_server.cc.o
/home/shiki/linux_-practice/OnlineJudge/bin/oj_server: oj_server/src/CMakeFiles/oj_server.dir/build.make
/home/shiki/linux_-practice/OnlineJudge/bin/oj_server: /usr/lib64/libpthread.so
/home/shiki/linux_-practice/OnlineJudge/bin/oj_server: /usr/lib64/libboost_system.so
/home/shiki/linux_-practice/OnlineJudge/bin/oj_server: /usr/local/lib/libctemplate.a
/home/shiki/linux_-practice/OnlineJudge/bin/oj_server: oj_server/src/CMakeFiles/oj_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shiki/linux_-practice/OnlineJudge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/shiki/linux_-practice/OnlineJudge/bin/oj_server"
	cd /home/shiki/linux_-practice/OnlineJudge/build/oj_server/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/oj_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
oj_server/src/CMakeFiles/oj_server.dir/build: /home/shiki/linux_-practice/OnlineJudge/bin/oj_server
.PHONY : oj_server/src/CMakeFiles/oj_server.dir/build

oj_server/src/CMakeFiles/oj_server.dir/clean:
	cd /home/shiki/linux_-practice/OnlineJudge/build/oj_server/src && $(CMAKE_COMMAND) -P CMakeFiles/oj_server.dir/cmake_clean.cmake
.PHONY : oj_server/src/CMakeFiles/oj_server.dir/clean

oj_server/src/CMakeFiles/oj_server.dir/depend:
	cd /home/shiki/linux_-practice/OnlineJudge/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shiki/linux_-practice/OnlineJudge /home/shiki/linux_-practice/OnlineJudge/oj_server/src /home/shiki/linux_-practice/OnlineJudge/build /home/shiki/linux_-practice/OnlineJudge/build/oj_server/src /home/shiki/linux_-practice/OnlineJudge/build/oj_server/src/CMakeFiles/oj_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : oj_server/src/CMakeFiles/oj_server.dir/depend

