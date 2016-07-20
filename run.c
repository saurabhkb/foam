#include <stdio.h>
#include "tmatrix.h"
#include "smatrix.h"

#define KEY_NEWLINE	13

int main() {
	int ch;
	SMatrix matrix;
	init_smatrix(&matrix);

	TMatrix tmtx;
	init_tmatrix(&tmtx);

	initscr();	// initialize
	keypad(stdscr, TRUE);	// extra keys
	cbreak();
	nonl();
	noecho();

	render(&matrix, &tmtx);

	while(1) {
		ch = wgetch(stdscr);
		switch(ch) {
			case KEY_LEFT:
				move_logical_cursor_left(&tmtx);
				break;
			case KEY_RIGHT:
				move_logical_cursor_right(&tmtx);
				break;
			case KEY_UP:
				move_logical_cursor_up(&tmtx);
				break;
			case KEY_DOWN:
				move_logical_cursor_down(&tmtx);
				break;
			case KEY_BACKSPACE:
				if(tmtx.logical_cursor_col == 0)
					delete_newline(&tmtx);
				else
					delete(&tmtx);
				break;
			case KEY_NEWLINE:
				insert_newline(&tmtx);
				break;
			default:
				insert(&tmtx, ch);
				break;
		}
		render(&matrix, &tmtx);
	}
	endwin();
	return 0;
}
