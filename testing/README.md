#### Test
Run `make`.

This will create a small executable (called `simulator`) which will parse an input test file containing specific syntax (described below) and print out the matrix (the doubly linked list of Line objects) as it would appear after those transformations have been performed.

Generally, the input test file must be named `inX` where `X` is the number of the test. Similarly, its corresponding output file must be named `outX`.

#### Syntax of `in*` files

LOAD <path> : load contents of file (if included, this **must** be the first instruction); the cursor remains at the beginning of the file.

INSSTR <string> : insert given string at cursor

BP : backspace

INSNL : insert newline at cursor

MVCRSR <row> <col> : move the cursor to specified row/col

MVCRSRUP: move the cursor up

MVCRSRDN : move the cursor down

MVCRSRRT : move the cursor right

MVCRSRLFT : move the cursor left


#### Syntax of `out*` files
Each line corresponds to a row in the matrix; first line &rarr; row 0, second line &rarr; row 1, etc.  
The content on each line must mimic exactly what is expected based on the transformations specified in the corresponding `in*` file.  
Finally, after the file description is over, on a newline, the final position of the cursor must be specified as `(row_num, col_num)`.  


#### Note
* Any line starting with a "#" is treated as a comment  
* Blank lines are ignored  
* The command length must **not** exceed 99 characters  
* The inserted strings should **not** contain any whitespaces*

A file `test1` could be created which contains some combination of the above commands (one per line).  
It could then be run as `./simulator test1`

A small script `run_tests.sh` is included which can be run directly. It will search for a folder named `tests` and run `simulator` on all files of type `in*` and diff with the corresponding `out*`.
