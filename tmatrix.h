#ifndef __TMATRIX
#define __TMATRIX

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ncurses.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

class SMatrix;

/*
TMatrix is the character matrix corresponding to the actual text. SMatrix contains only a cropped window corresponding to the actual screen.
*/
class TMatrix {
private:
	std::vector<std::string> text;	/* stores the text matrix */
	int logical_cursor_row;
	int logical_cursor_col;
public:
	TMatrix();
	/* character manipulation methods */
	void insert_ch(const char);
	void delete_ch();
	void insert_newline();
	void delete_newline();

	/* cursor movement methods */
	void move_logical_cursor_up();
	void move_logical_cursor_down();
	void move_logical_cursor_left();
	void move_logical_cursor_right();

	/* friend methods for rendering */
	friend void render(SMatrix&, TMatrix&);
	friend void run_loop(SMatrix&, TMatrix&);
};

#endif
