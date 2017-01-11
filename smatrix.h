#ifndef __SMATRIX
#define __SMATRIX
#include "tmatrix.h"

/*
SMatrix is the character matrix corresponding to the screen
*/
class SMatrix {
private:
	unsigned int screen_cursor_row;
	unsigned int screen_cursor_col;
	unsigned int y_offset;	/* line number from top of screen */
public:
	SMatrix();
	~SMatrix();
	friend void render(SMatrix&, TMatrix&);
};

#endif
