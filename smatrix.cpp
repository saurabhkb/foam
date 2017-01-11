#include "smatrix.h"

SMatrix::SMatrix() {
	screen_cursor_row = screen_cursor_col = y_offset = 0;
}

SMatrix::~SMatrix() {
	endwin();
}
