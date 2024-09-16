# BrickGame Tetris
The implementation of the game "Tetris" in the C programming language.
### About the program: 
- The program consists of two parts: a library that implements the logic of the Tetris game, and a terminal interface using the `ncurses` library.
- The program library code is located in the folder `src/brick_game/tetris`. The code with the program interface is located in the `src/gui/cli` folder.
- The program build is configured using a Makefile with a standard set of goals for GNU programs: all, install, uninstall, clean, dvi, dist, test, gcov_report.
- The library is covered with unit tests using the `check` library.
- The game has the following mechanics: rotation of figures, moving a figure horizontally, accelerating the fall of a figure, showing the next figure, destroying filled lines, ending the game when reaching the upper limit of the playing field;
- Added support for all buttons provided on the physical console for control:
  - Enter - start of the game,
  - Space - pause,
  - Esc - end of the game,
  - Left arrow — move the figure to the left,
  - Right arrow — movement of the figure to the right,
  - Down arrow — drop of the figure,
  - Enter - rotation of the shape.
- The playing field is 10 pixels wide and 20 pixels high.
- There is information about scoring and record in the game.
Points will be awarded as follows:
  - 1 line — 100 points;
  - 2 lines — 300 points;
  - 3 lines — 700 points;
  - 4 lines — 1500 points.
- Implemented level mechanics. Each time a player scores 600 points, the level increases by 1. Increasing the level increases the speed of movement of the pieces. The maximum number of levels is 10.
  
To install doxygen:
- Ubuntu / Linux: `sudo apt-get install doxygen`

![figures](img/figures.png)