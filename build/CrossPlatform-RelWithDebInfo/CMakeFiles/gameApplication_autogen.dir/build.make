# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = /home/yareg/gameApplication

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yareg/gameApplication/build/CrossPlatform-RelWithDebInfo

# Utility rule file for gameApplication_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/gameApplication_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gameApplication_autogen.dir/progress.make

CMakeFiles/gameApplication_autogen: gameApplication_autogen/timestamp

gameApplication_autogen/timestamp: /usr/lib/qt6/moc
gameApplication_autogen/timestamp: /usr/lib/qt6/uic
gameApplication_autogen/timestamp: CMakeFiles/gameApplication_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/yareg/gameApplication/build/CrossPlatform-RelWithDebInfo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target gameApplication"
	/usr/bin/cmake -E cmake_autogen /home/yareg/gameApplication/build/CrossPlatform-RelWithDebInfo/CMakeFiles/gameApplication_autogen.dir/AutogenInfo.json RelWithDebInfo
	/usr/bin/cmake -E touch /home/yareg/gameApplication/build/CrossPlatform-RelWithDebInfo/gameApplication_autogen/timestamp

CMakeFiles/gameApplication_autogen.dir/codegen:
.PHONY : CMakeFiles/gameApplication_autogen.dir/codegen

gameApplication_autogen: CMakeFiles/gameApplication_autogen
gameApplication_autogen: gameApplication_autogen/timestamp
gameApplication_autogen: CMakeFiles/gameApplication_autogen.dir/build.make
.PHONY : gameApplication_autogen

# Rule to build all files generated by this target.
CMakeFiles/gameApplication_autogen.dir/build: gameApplication_autogen
.PHONY : CMakeFiles/gameApplication_autogen.dir/build

CMakeFiles/gameApplication_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gameApplication_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gameApplication_autogen.dir/clean

CMakeFiles/gameApplication_autogen.dir/depend:
	cd /home/yareg/gameApplication/build/CrossPlatform-RelWithDebInfo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yareg/gameApplication /home/yareg/gameApplication /home/yareg/gameApplication/build/CrossPlatform-RelWithDebInfo /home/yareg/gameApplication/build/CrossPlatform-RelWithDebInfo /home/yareg/gameApplication/build/CrossPlatform-RelWithDebInfo/CMakeFiles/gameApplication_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/gameApplication_autogen.dir/depend

