#include "tmatrix.h"
#include <iostream>
#include <stdlib.h>


void TMatrix::insert_ch(const char ch) {
	text[logical_cursor_row].insert(logical_cursor_col, 1, ch);
	logical_cursor_col++;
}

void TMatrix::delete_ch() {
	if(logical_cursor_col == 0) return;
	text[logical_cursor_row].erase(logical_cursor_col - 1, 1);
	logical_cursor_col--;
}

void TMatrix::insert_newline() {
	std::string extra_line(text[logical_cursor_row], logical_cursor_col, std::string::npos);
	text[logical_cursor_row].erase(logical_cursor_col, std::string::npos);

	std::vector<std::string>::iterator it = text.begin();
	text.insert(it + logical_cursor_row + 1, extra_line);

	logical_cursor_row++;
	logical_cursor_col = 0;
}

void TMatrix::delete_newline() {
	if(logical_cursor_row == 0) return;

	text[logical_cursor_row - 1] += text[logical_cursor_row];

	std::vector<std::string>::iterator it = text.begin();
	text.erase(it + logical_cursor_row, it + logical_cursor_row + 1);

	logical_cursor_row--;
	logical_cursor_col = text[logical_cursor_row].length();
}

TMatrix::TMatrix() {
	text.push_back("");	/* initialize first empty line */
	logical_cursor_col = logical_cursor_row = 0;	/* set cursor to the top right position */
}


void TMatrix::move_logical_cursor_up() {
	if(logical_cursor_row > 0) {
		logical_cursor_row--;
	}

	/* if upper row has smaller length, move cursor to the end of that line */
	if(text[logical_cursor_row].length() < (unsigned int) logical_cursor_col) {
		logical_cursor_col = text[logical_cursor_row].length();
	}
}

void TMatrix::move_logical_cursor_down() {
	if(logical_cursor_row < 0 || logical_cursor_col < 0) return;
	if((unsigned int) logical_cursor_row < text.size() - 1) {
		logical_cursor_row++;
	}

	if(text[logical_cursor_row].length() < (unsigned int) logical_cursor_col)
		logical_cursor_col = text[logical_cursor_row].length();
}

void TMatrix::move_logical_cursor_left() {
	if(logical_cursor_col > 0)
		logical_cursor_col--;
}

void TMatrix::move_logical_cursor_right() {
	if(logical_cursor_row < 0 || logical_cursor_col < 0) return;

	if((unsigned int) logical_cursor_col < text[logical_cursor_row].length())
		logical_cursor_col++;
}
