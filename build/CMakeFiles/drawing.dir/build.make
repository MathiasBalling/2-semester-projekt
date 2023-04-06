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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mathiaschristiansen/Documents/2-semester-projekt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mathiaschristiansen/Documents/2-semester-projekt/build

# Include any dependencies generated for this target.
include CMakeFiles/drawing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/drawing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/drawing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/drawing.dir/flags.make

CMakeFiles/drawing.dir/src/AI.cpp.o: CMakeFiles/drawing.dir/flags.make
CMakeFiles/drawing.dir/src/AI.cpp.o: /Users/mathiaschristiansen/Documents/2-semester-projekt/src/AI.cpp
CMakeFiles/drawing.dir/src/AI.cpp.o: CMakeFiles/drawing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/drawing.dir/src/AI.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drawing.dir/src/AI.cpp.o -MF CMakeFiles/drawing.dir/src/AI.cpp.o.d -o CMakeFiles/drawing.dir/src/AI.cpp.o -c /Users/mathiaschristiansen/Documents/2-semester-projekt/src/AI.cpp

CMakeFiles/drawing.dir/src/AI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drawing.dir/src/AI.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathiaschristiansen/Documents/2-semester-projekt/src/AI.cpp > CMakeFiles/drawing.dir/src/AI.cpp.i

CMakeFiles/drawing.dir/src/AI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drawing.dir/src/AI.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathiaschristiansen/Documents/2-semester-projekt/src/AI.cpp -o CMakeFiles/drawing.dir/src/AI.cpp.s

CMakeFiles/drawing.dir/src/Board.cpp.o: CMakeFiles/drawing.dir/flags.make
CMakeFiles/drawing.dir/src/Board.cpp.o: /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Board.cpp
CMakeFiles/drawing.dir/src/Board.cpp.o: CMakeFiles/drawing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/drawing.dir/src/Board.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drawing.dir/src/Board.cpp.o -MF CMakeFiles/drawing.dir/src/Board.cpp.o.d -o CMakeFiles/drawing.dir/src/Board.cpp.o -c /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Board.cpp

CMakeFiles/drawing.dir/src/Board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drawing.dir/src/Board.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Board.cpp > CMakeFiles/drawing.dir/src/Board.cpp.i

CMakeFiles/drawing.dir/src/Board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drawing.dir/src/Board.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Board.cpp -o CMakeFiles/drawing.dir/src/Board.cpp.s

CMakeFiles/drawing.dir/src/Cell.cpp.o: CMakeFiles/drawing.dir/flags.make
CMakeFiles/drawing.dir/src/Cell.cpp.o: /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Cell.cpp
CMakeFiles/drawing.dir/src/Cell.cpp.o: CMakeFiles/drawing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/drawing.dir/src/Cell.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drawing.dir/src/Cell.cpp.o -MF CMakeFiles/drawing.dir/src/Cell.cpp.o.d -o CMakeFiles/drawing.dir/src/Cell.cpp.o -c /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Cell.cpp

CMakeFiles/drawing.dir/src/Cell.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drawing.dir/src/Cell.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Cell.cpp > CMakeFiles/drawing.dir/src/Cell.cpp.i

CMakeFiles/drawing.dir/src/Cell.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drawing.dir/src/Cell.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Cell.cpp -o CMakeFiles/drawing.dir/src/Cell.cpp.s

CMakeFiles/drawing.dir/src/ChessFrame.cpp.o: CMakeFiles/drawing.dir/flags.make
CMakeFiles/drawing.dir/src/ChessFrame.cpp.o: /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ChessFrame.cpp
CMakeFiles/drawing.dir/src/ChessFrame.cpp.o: CMakeFiles/drawing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/drawing.dir/src/ChessFrame.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drawing.dir/src/ChessFrame.cpp.o -MF CMakeFiles/drawing.dir/src/ChessFrame.cpp.o.d -o CMakeFiles/drawing.dir/src/ChessFrame.cpp.o -c /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ChessFrame.cpp

CMakeFiles/drawing.dir/src/ChessFrame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drawing.dir/src/ChessFrame.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ChessFrame.cpp > CMakeFiles/drawing.dir/src/ChessFrame.cpp.i

CMakeFiles/drawing.dir/src/ChessFrame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drawing.dir/src/ChessFrame.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ChessFrame.cpp -o CMakeFiles/drawing.dir/src/ChessFrame.cpp.s

CMakeFiles/drawing.dir/src/ChessPanel.cpp.o: CMakeFiles/drawing.dir/flags.make
CMakeFiles/drawing.dir/src/ChessPanel.cpp.o: /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ChessPanel.cpp
CMakeFiles/drawing.dir/src/ChessPanel.cpp.o: CMakeFiles/drawing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/drawing.dir/src/ChessPanel.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drawing.dir/src/ChessPanel.cpp.o -MF CMakeFiles/drawing.dir/src/ChessPanel.cpp.o.d -o CMakeFiles/drawing.dir/src/ChessPanel.cpp.o -c /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ChessPanel.cpp

CMakeFiles/drawing.dir/src/ChessPanel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drawing.dir/src/ChessPanel.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ChessPanel.cpp > CMakeFiles/drawing.dir/src/ChessPanel.cpp.i

CMakeFiles/drawing.dir/src/ChessPanel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drawing.dir/src/ChessPanel.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ChessPanel.cpp -o CMakeFiles/drawing.dir/src/ChessPanel.cpp.s

CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.o: CMakeFiles/drawing.dir/flags.make
CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.o: /Users/mathiaschristiansen/Documents/2-semester-projekt/src/DeadPieceWindow.cpp
CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.o: CMakeFiles/drawing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.o -MF CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.o.d -o CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.o -c /Users/mathiaschristiansen/Documents/2-semester-projekt/src/DeadPieceWindow.cpp

CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathiaschristiansen/Documents/2-semester-projekt/src/DeadPieceWindow.cpp > CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.i

CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathiaschristiansen/Documents/2-semester-projekt/src/DeadPieceWindow.cpp -o CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.s

CMakeFiles/drawing.dir/src/ModBus.cpp.o: CMakeFiles/drawing.dir/flags.make
CMakeFiles/drawing.dir/src/ModBus.cpp.o: /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ModBus.cpp
CMakeFiles/drawing.dir/src/ModBus.cpp.o: CMakeFiles/drawing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/drawing.dir/src/ModBus.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drawing.dir/src/ModBus.cpp.o -MF CMakeFiles/drawing.dir/src/ModBus.cpp.o.d -o CMakeFiles/drawing.dir/src/ModBus.cpp.o -c /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ModBus.cpp

CMakeFiles/drawing.dir/src/ModBus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drawing.dir/src/ModBus.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ModBus.cpp > CMakeFiles/drawing.dir/src/ModBus.cpp.i

CMakeFiles/drawing.dir/src/ModBus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drawing.dir/src/ModBus.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathiaschristiansen/Documents/2-semester-projekt/src/ModBus.cpp -o CMakeFiles/drawing.dir/src/ModBus.cpp.s

CMakeFiles/drawing.dir/src/Piece.cpp.o: CMakeFiles/drawing.dir/flags.make
CMakeFiles/drawing.dir/src/Piece.cpp.o: /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Piece.cpp
CMakeFiles/drawing.dir/src/Piece.cpp.o: CMakeFiles/drawing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/drawing.dir/src/Piece.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drawing.dir/src/Piece.cpp.o -MF CMakeFiles/drawing.dir/src/Piece.cpp.o.d -o CMakeFiles/drawing.dir/src/Piece.cpp.o -c /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Piece.cpp

CMakeFiles/drawing.dir/src/Piece.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drawing.dir/src/Piece.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Piece.cpp > CMakeFiles/drawing.dir/src/Piece.cpp.i

CMakeFiles/drawing.dir/src/Piece.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drawing.dir/src/Piece.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathiaschristiansen/Documents/2-semester-projekt/src/Piece.cpp -o CMakeFiles/drawing.dir/src/Piece.cpp.s

CMakeFiles/drawing.dir/src/QueueWindow.cpp.o: CMakeFiles/drawing.dir/flags.make
CMakeFiles/drawing.dir/src/QueueWindow.cpp.o: /Users/mathiaschristiansen/Documents/2-semester-projekt/src/QueueWindow.cpp
CMakeFiles/drawing.dir/src/QueueWindow.cpp.o: CMakeFiles/drawing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/drawing.dir/src/QueueWindow.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drawing.dir/src/QueueWindow.cpp.o -MF CMakeFiles/drawing.dir/src/QueueWindow.cpp.o.d -o CMakeFiles/drawing.dir/src/QueueWindow.cpp.o -c /Users/mathiaschristiansen/Documents/2-semester-projekt/src/QueueWindow.cpp

CMakeFiles/drawing.dir/src/QueueWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drawing.dir/src/QueueWindow.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathiaschristiansen/Documents/2-semester-projekt/src/QueueWindow.cpp > CMakeFiles/drawing.dir/src/QueueWindow.cpp.i

CMakeFiles/drawing.dir/src/QueueWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drawing.dir/src/QueueWindow.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathiaschristiansen/Documents/2-semester-projekt/src/QueueWindow.cpp -o CMakeFiles/drawing.dir/src/QueueWindow.cpp.s

CMakeFiles/drawing.dir/src/main.cpp.o: CMakeFiles/drawing.dir/flags.make
CMakeFiles/drawing.dir/src/main.cpp.o: /Users/mathiaschristiansen/Documents/2-semester-projekt/src/main.cpp
CMakeFiles/drawing.dir/src/main.cpp.o: CMakeFiles/drawing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/drawing.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/drawing.dir/src/main.cpp.o -MF CMakeFiles/drawing.dir/src/main.cpp.o.d -o CMakeFiles/drawing.dir/src/main.cpp.o -c /Users/mathiaschristiansen/Documents/2-semester-projekt/src/main.cpp

CMakeFiles/drawing.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/drawing.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathiaschristiansen/Documents/2-semester-projekt/src/main.cpp > CMakeFiles/drawing.dir/src/main.cpp.i

CMakeFiles/drawing.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/drawing.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathiaschristiansen/Documents/2-semester-projekt/src/main.cpp -o CMakeFiles/drawing.dir/src/main.cpp.s

# Object files for target drawing
drawing_OBJECTS = \
"CMakeFiles/drawing.dir/src/AI.cpp.o" \
"CMakeFiles/drawing.dir/src/Board.cpp.o" \
"CMakeFiles/drawing.dir/src/Cell.cpp.o" \
"CMakeFiles/drawing.dir/src/ChessFrame.cpp.o" \
"CMakeFiles/drawing.dir/src/ChessPanel.cpp.o" \
"CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.o" \
"CMakeFiles/drawing.dir/src/ModBus.cpp.o" \
"CMakeFiles/drawing.dir/src/Piece.cpp.o" \
"CMakeFiles/drawing.dir/src/QueueWindow.cpp.o" \
"CMakeFiles/drawing.dir/src/main.cpp.o"

# External object files for target drawing
drawing_EXTERNAL_OBJECTS =

drawing: CMakeFiles/drawing.dir/src/AI.cpp.o
drawing: CMakeFiles/drawing.dir/src/Board.cpp.o
drawing: CMakeFiles/drawing.dir/src/Cell.cpp.o
drawing: CMakeFiles/drawing.dir/src/ChessFrame.cpp.o
drawing: CMakeFiles/drawing.dir/src/ChessPanel.cpp.o
drawing: CMakeFiles/drawing.dir/src/DeadPieceWindow.cpp.o
drawing: CMakeFiles/drawing.dir/src/ModBus.cpp.o
drawing: CMakeFiles/drawing.dir/src/Piece.cpp.o
drawing: CMakeFiles/drawing.dir/src/QueueWindow.cpp.o
drawing: CMakeFiles/drawing.dir/src/main.cpp.o
drawing: CMakeFiles/drawing.dir/build.make
drawing: CMakeFiles/drawing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable drawing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/drawing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/drawing.dir/build: drawing
.PHONY : CMakeFiles/drawing.dir/build

CMakeFiles/drawing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/drawing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/drawing.dir/clean

CMakeFiles/drawing.dir/depend:
	cd /Users/mathiaschristiansen/Documents/2-semester-projekt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mathiaschristiansen/Documents/2-semester-projekt /Users/mathiaschristiansen/Documents/2-semester-projekt /Users/mathiaschristiansen/Documents/2-semester-projekt/build /Users/mathiaschristiansen/Documents/2-semester-projekt/build /Users/mathiaschristiansen/Documents/2-semester-projekt/build/CMakeFiles/drawing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/drawing.dir/depend

