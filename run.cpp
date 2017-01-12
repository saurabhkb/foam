#include <string.h>
#include "tmatrix.h"
#include "smatrix.h"

inline unsigned int min(unsigned int a, unsigned int b) {
	if(a > b) return b;
	return a;
}

/* render the line with the string arr */
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

/* main function which goes through the text matrix and decides what submatrix actually
appears on the screen based on the screen dimensions */
void render(SMatrix& smtx, TMatrix& tmtx) {
	unsigned int i = 0;
	clear();

	/* shift screen window up or down if needed (if the size of the text matrix is bigger 
	than the size of the screen window */
	smtx.screen_cursor_col = tmtx.logical_cursor_col % COLS;
	if(tmtx.logical_cursor_row - smtx.y_offset >= LINES) {
		/* logical cursor is too far down, so update y offset */
		smtx.y_offset = tmtx.logical_cursor_row - LINES + 1;
		smtx.screen_cursor_row = tmtx.logical_cursor_row - smtx.y_offset;
	} else if(tmtx.logical_cursor_row <= smtx.y_offset) {
		/* logical cursor is above y offset */
		smtx.y_offset = tmtx.logical_cursor_row;
		smtx.screen_cursor_row = 0;
	} else {
		/* all normal */
		smtx.screen_cursor_row = tmtx.logical_cursor_row - smtx.y_offset;
	}

	/* start rendering */
	for(unsigned int j = smtx.y_offset; j < min((unsigned int) smtx.y_offset + LINES, tmtx.text.size()); j++) {
		i += render_line(i, tmtx.text[j]);
	}

	/* move the cursor to the position calculated */
	move(smtx.screen_cursor_row, smtx.screen_cursor_col);
	refresh();
}

/* loop which reads user input and calls render to show it on the screen */
void run_loop(SMatrix& smtx, TMatrix& tmtx) {
	unsigned int ch;
	const int KEY_NEWLINE = 13;

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
	SMatrix smtx;
	TMatrix tmtx;

	initscr();	/* initialize; stick to the standard default window */
	LINES = 10;
	keypad(stdscr, TRUE);	/* extra keys */
	cbreak();	/* no input buffering */
	nonl();	/* better newline handling */
	noecho();	/* prevent echo */

	run_loop(smtx, tmtx);

	endwin();	/* restore to pre-ncurses state */
	return 0;
}
