#include "smatrix.h"

#define CEIL(a, b) (((a) / (b)) + (((a) % (b)) > 0 ? 1 : 0))

// TODO probably a more efficient way of doing this
void render(SMatrix *smtx, TMatrix *tmtx) {
	int i = 0, len;
	int text_line_number = 0, num_screen_lines;
	Line *top;
	clear();

	// based on the number of screen lines each text line takes, find the position of the cursor
	Line *iter = tmtx->head;
	while(iter) {
		if(text_line_number == tmtx->logical_cursor_row) {
			smtx->screen_cursor_row = i + tmtx->logical_cursor_col / COLS;
		}
		len = strlen(iter->arr);
		i += (len == 0) ? 1 : CEIL(len, COLS);
		text_line_number++;
		iter = iter->next;
	}
	smtx->screen_cursor_col = tmtx->logical_cursor_col % COLS;

	// increment the y_offset by the number of screen lines of the topmost line currently on the screen
	// note that we must increment i by the number of screen lines each text line occupies (not simply by 1 each time)
	top = tmtx->logical_cursor_line;
	i = 0;
	while(top->prev && i < LINES) {
		top = top->prev;
		len = strlen(top->arr);
		i += (len == 0) ? 1 : CEIL(len, COLS);
	}
	len = strlen(top->arr);
	num_screen_lines = (len == 0) ? 1 : CEIL(len, COLS);

	// set y_offset as required
	if(smtx->screen_cursor_row - smtx->y_offset >= LINES) {
		smtx->y_offset += num_screen_lines;
	}
	if(smtx->screen_cursor_row < smtx->y_offset) {
		smtx->y_offset -= num_screen_lines;
		if(smtx->y_offset < 0) smtx->y_offset = 0;
	}

	// go to the actual text line that is going to be rendered on the screen
	iter = tmtx->head;
	i = 0;
	while(i < smtx->y_offset && iter) {
		len = strlen(iter->arr);
		i += (len == 0) ? 1 : CEIL(len, COLS);
		iter = iter->next;
	}

	// start rendering
	i = 0;
	while(iter) {
		i += render_line(i, iter->arr);
		iter = iter->next;
	}

	// move the cursor to the position calculated offset by the y_offset
	move(smtx->screen_cursor_row - smtx->y_offset, smtx->screen_cursor_col);
	refresh();
}

int render_line(int pos, char *arr) {
	int i = 0;
	char *start = arr;
	while(strlen(start) > COLS) {
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

void init_smatrix(SMatrix *smtx) {
	smtx->screen_cursor_row = smtx->screen_cursor_col = smtx->y_offset = 0;
}

void destroy_smatrix(SMatrix *smtx) {
	endwin();
}
