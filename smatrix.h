#ifndef __SMATRIX
#define __SMATRIX
#include "tmatrix.h"

/*
SMatrix is the character matrix corresponding to the screen
*/
class SMatrix {
private:
	int screen_cursor_row;
	int screen_cursor_col;
	int y_offset;	/* line number from top of screen */
public:
	SMatrix();
	~SMatrix();
	friend void render(SMatrix&, TMatrix&);
};

#endif
