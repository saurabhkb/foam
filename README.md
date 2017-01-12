## Foam

Foam is a basic text editor written in C++ using ncurses.

To use it, run `make` and then `./editor`.

#### Features
* write stuff on the screen - insert/delete characters
* navigate using the cursor

#### Working
* `tmatrix` is a matrix (vector of strings) which contains the text entered by the user.
*  `smatrix` is a matrix which represents the screen which will in general be smaller than the text matrix and therefore represents a smaller cutout of the `tmatrix`.
*  `run.cpp` contains the actual logic which reads input from the keyboard and updates the `tmatrix` and also calculates the screen matrix `smatrix`  

#### To Do
* save to file
* add more features like undo/redo, cut/copy/paste, etc.
