#include <stdio.h>
#include <string.h>
#include "tmatrix.h"
#include "smatrix.h"

const int KEY_NEWLINE = 13;

#define CEIL(a, b) (((a) / (b)) + (((a) % (b)) > 0 ? 1 : 0))

int render_line(int pos, std::string arr) {
	int i = 0;
	char *start = &arr[0];
	while((int) strlen(start) > COLS) {
		mvaddnstr(pos + i, 0, start, COLS);
		i++;
		start += COLS;
	}
	if(strlen(start) > 0) {
		mvaddstr(pos + i, 0, start);
		i++;
	}
	return i > 0 ? i : 1;
}

void render(SMatrix& smtx, TMatrix& tmtx) {
	unsigned int i = 0, len;
	unsigned int text_line_number = 0, num_screen_lines = 0;
	clear();

	for(unsigned int j = 0; j < tmtx.text.size(); j++) {
		if(text_line_number == tmtx.logical_cursor_row)
			smtx.screen_cursor_row = num_screen_lines + tmtx.logical_cursor_col / COLS;

		/*
		if line is empty, it will take up only one screen line otherwise,
		the number of screen lines taken will depend on the length of the text line
		and the number of columns in the screen
		*/
		len = tmtx.text[j].length();
		num_screen_lines += (len == 0) ? 1 : CEIL(len, COLS);
		text_line_number++;
	}
	smtx.screen_cursor_col = tmtx.logical_cursor_col % COLS;

	/* increment the y_offset by the number of screen lines of the topmost line currently on the screen */
	/* note that we must increment i by the number of screen lines each text line occupies (not simply by 1 each time) */

	/* set y_offset as required */
	if((int) (smtx.screen_cursor_row - smtx.y_offset) >= LINES) {
		smtx.y_offset += num_screen_lines;
	}
	if(smtx.screen_cursor_row < smtx.y_offset) {
		smtx.y_offset -= num_screen_lines;
		if(smtx.y_offset < 0) smtx.y_offset = 0;
	}

	/* start rendering */
	i = 0;
	for(unsigned int j = smtx.y_offset; j < tmtx.text.size(); j++) {
		i += render_line(i, tmtx.text[j]);
	}

	/* move the cursor to the position calculated offset by the y_offset */
	move(smtx.screen_cursor_row - smtx.y_offset, smtx.screen_cursor_col);
	printw("nsl:%d, %d, %d\n", num_screen_lines, smtx.screen_cursor_row, LINES);
	refresh();
}


void run_loop(SMatrix& smtx, TMatrix& tmtx) {
	unsigned int ch;

	render(smtx, tmtx);
	while(1) {
		ch = wgetch(stdscr);
		switch(ch) {
			case KEY_LEFT:
				tmtx.move_logical_cursor_left();
				break;
			case KEY_RIGHT:
				tmtx.move_logical_cursor_right();
				break;
			case KEY_UP:
				tmtx.move_logical_cursor_up();
				break;
			case KEY_DOWN:
				tmtx.move_logical_cursor_down();
				break;
			case KEY_BACKSPACE:
				if(tmtx.logical_cursor_col == 0)
					tmtx.delete_newline();
				else
					tmtx.delete_ch();
				break;
			case KEY_NEWLINE:
				tmtx.insert_newline();
				break;
			default:
				tmtx.insert_ch(ch);
				break;
		}
		render(smtx, tmtx);
	}
}

int main() {
	SMatrix matrix;
	TMatrix tmtx;

	initscr();	// initialize
	keypad(stdscr, TRUE);	// extra keys
	cbreak();
	nonl();
	noecho();

	run_loop(matrix, tmtx);

	endwin();
	return 0;
}
