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
CMAKE_BINARY_DIR = /home/yareg/gameApplication/build/CrossPlatform-Debug

# Include any dependencies generated for this target.
include CMakeFiles/server_app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server_app.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server_app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server_app.dir/flags.make

server_app_autogen/timestamp: /usr/lib/qt6/moc
server_app_autogen/timestamp: /usr/lib/qt6/uic
server_app_autogen/timestamp: CMakeFiles/server_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/yareg/gameApplication/build/CrossPlatform-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target server_app"
	/usr/bin/cmake -E cmake_autogen /home/yareg/gameApplication/build/CrossPlatform-Debug/CMakeFiles/server_app_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/yareg/gameApplication/build/CrossPlatform-Debug/server_app_autogen/timestamp

CMakeFiles/server_app.dir/codegen:
.PHONY : CMakeFiles/server_app.dir/codegen

CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.o: CMakeFiles/server_app.dir/flags.make
CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.o: server_app_autogen/mocs_compilation.cpp
CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.o: CMakeFiles/server_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yareg/gameApplication/build/CrossPlatform-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.o -MF CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.o -c /home/yareg/gameApplication/build/CrossPlatform-Debug/server_app_autogen/mocs_compilation.cpp

CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yareg/gameApplication/build/CrossPlatform-Debug/server_app_autogen/mocs_compilation.cpp > CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.i

CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yareg/gameApplication/build/CrossPlatform-Debug/server_app_autogen/mocs_compilation.cpp -o CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.s

CMakeFiles/server_app.dir/gameServer/main.cpp.o: CMakeFiles/server_app.dir/flags.make
CMakeFiles/server_app.dir/gameServer/main.cpp.o: /home/yareg/gameApplication/gameServer/main.cpp
CMakeFiles/server_app.dir/gameServer/main.cpp.o: CMakeFiles/server_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yareg/gameApplication/build/CrossPlatform-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server_app.dir/gameServer/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server_app.dir/gameServer/main.cpp.o -MF CMakeFiles/server_app.dir/gameServer/main.cpp.o.d -o CMakeFiles/server_app.dir/gameServer/main.cpp.o -c /home/yareg/gameApplication/gameServer/main.cpp

CMakeFiles/server_app.dir/gameServer/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server_app.dir/gameServer/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yareg/gameApplication/gameServer/main.cpp > CMakeFiles/server_app.dir/gameServer/main.cpp.i

CMakeFiles/server_app.dir/gameServer/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server_app.dir/gameServer/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yareg/gameApplication/gameServer/main.cpp -o CMakeFiles/server_app.dir/gameServer/main.cpp.s

CMakeFiles/server_app.dir/gameServer/gameServer.cpp.o: CMakeFiles/server_app.dir/flags.make
CMakeFiles/server_app.dir/gameServer/gameServer.cpp.o: /home/yareg/gameApplication/gameServer/gameServer.cpp
CMakeFiles/server_app.dir/gameServer/gameServer.cpp.o: CMakeFiles/server_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yareg/gameApplication/build/CrossPlatform-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server_app.dir/gameServer/gameServer.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server_app.dir/gameServer/gameServer.cpp.o -MF CMakeFiles/server_app.dir/gameServer/gameServer.cpp.o.d -o CMakeFiles/server_app.dir/gameServer/gameServer.cpp.o -c /home/yareg/gameApplication/gameServer/gameServer.cpp

CMakeFiles/server_app.dir/gameServer/gameServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server_app.dir/gameServer/gameServer.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yareg/gameApplication/gameServer/gameServer.cpp > CMakeFiles/server_app.dir/gameServer/gameServer.cpp.i

CMakeFiles/server_app.dir/gameServer/gameServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server_app.dir/gameServer/gameServer.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yareg/gameApplication/gameServer/gameServer.cpp -o CMakeFiles/server_app.dir/gameServer/gameServer.cpp.s

# Object files for target server_app
server_app_OBJECTS = \
"CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/server_app.dir/gameServer/main.cpp.o" \
"CMakeFiles/server_app.dir/gameServer/gameServer.cpp.o"

# External object files for target server_app
server_app_EXTERNAL_OBJECTS =

server_app: CMakeFiles/server_app.dir/server_app_autogen/mocs_compilation.cpp.o
server_app: CMakeFiles/server_app.dir/gameServer/main.cpp.o
server_app: CMakeFiles/server_app.dir/gameServer/gameServer.cpp.o
server_app: CMakeFiles/server_app.dir/build.make
server_app: CMakeFiles/server_app.dir/compiler_depend.ts
server_app: /usr/lib/libQt6Widgets.so.6.8.2
server_app: /usr/lib/libQt6WebSockets.so.6.8.2
server_app: /usr/lib/libQt6Gui.so.6.8.2
server_app: /usr/lib/libGLX.so
server_app: /usr/lib/libOpenGL.so
server_app: /usr/lib/libQt6Network.so.6.8.2
server_app: /usr/lib/libQt6Core.so.6.8.2
server_app: CMakeFiles/server_app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/yareg/gameApplication/build/CrossPlatform-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable server_app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server_app.dir/build: server_app
.PHONY : CMakeFiles/server_app.dir/build

CMakeFiles/server_app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server_app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server_app.dir/clean

CMakeFiles/server_app.dir/depend: server_app_autogen/timestamp
	cd /home/yareg/gameApplication/build/CrossPlatform-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yareg/gameApplication /home/yareg/gameApplication /home/yareg/gameApplication/build/CrossPlatform-Debug /home/yareg/gameApplication/build/CrossPlatform-Debug /home/yareg/gameApplication/build/CrossPlatform-Debug/CMakeFiles/server_app.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/server_app.dir/depend

