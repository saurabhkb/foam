#include "tmatrix.h"

void insert(TMatrix *tmtx, int ch) {
	int i = 0;
	int len = strlen(tmtx->logical_cursor_line->arr);

	// resize arr if necessary
	if(len >= tmtx->logical_cursor_line->exp * BUF_SIZE - 1) {
		tmtx->logical_cursor_line->exp *= 2;
		tmtx->logical_cursor_line->arr = (char *)realloc(tmtx->logical_cursor_line->arr, tmtx->logical_cursor_line->exp * BUF_SIZE);
	}

	// shift all characters one ahead along with \0
	for(i = len; i >= tmtx->logical_cursor_col; i--)
		tmtx->logical_cursor_line->arr[i + 1] = tmtx->logical_cursor_line->arr[i];

	// add in character
	tmtx->logical_cursor_line->arr[tmtx->logical_cursor_col] = ch;
	tmtx->logical_cursor_col++;
}

void delete(TMatrix *tmtx) {
	int i;
	// shift all characters one back (loop includes the \0)

	if(tmtx->logical_cursor_col == 0) return;
	for(i = tmtx->logical_cursor_col - 1; tmtx->logical_cursor_line->arr[i]; i++)
		tmtx->logical_cursor_line->arr[i] = tmtx->logical_cursor_line->arr[i + 1];
	tmtx->logical_cursor_col--;
}

void insert_newline(TMatrix *tmtx) {
	// point where current line is to be broken
	char *breakpoint = &(tmtx->logical_cursor_line->arr[tmtx->logical_cursor_col]);

	// create a new line and insert into linked list
	Line *extra_line = new_line();
	extra_line->next = tmtx->logical_cursor_line->next;
	if(tmtx->logical_cursor_line->next)
		tmtx->logical_cursor_line->next->prev = extra_line;
	extra_line->prev = tmtx->logical_cursor_line;
	tmtx->logical_cursor_line->next = extra_line;

	// make sure that the new line has enough space (account for the \0, hence using >= and not >) and then:
	// copy over content and set \0 to override the content of the previous line
	while(strlen(breakpoint) >= extra_line->exp * BUF_SIZE)
		extra_line->exp *= 2;
	extra_line->arr = (char *)realloc(extra_line->arr, extra_line->exp * BUF_SIZE);
	strcpy(extra_line->arr, breakpoint);
	extra_line->arr[strlen(breakpoint)] = '\0';
	tmtx->logical_cursor_line->arr[tmtx->logical_cursor_col] = '\0';

	// update tail if we need to
	if(extra_line->next == NULL) {
		tmtx->tail = extra_line;
	}
	tmtx->logical_cursor_line = extra_line;
	tmtx->logical_cursor_row++;
	tmtx->logical_cursor_col = 0;
}

void delete_newline(TMatrix *tmtx) {
	if(tmtx->logical_cursor_line == tmtx->head) return;
	// store this for moving cursor at the end
	int prev_line_length = strlen(tmtx->logical_cursor_line->prev->arr);

	Line *temp = tmtx->logical_cursor_line->prev;
	// concatenate this line to previous line
	while(strlen(temp->arr) + strlen(tmtx->logical_cursor_line->arr) >= temp->exp * BUF_SIZE)
		temp->exp *= 2;
	temp->arr = (char *)realloc(temp->arr, temp->exp * BUF_SIZE);
	strcat(tmtx->logical_cursor_line->prev->arr, tmtx->logical_cursor_line->arr);

	// update previous line to point next to next line
	tmtx->logical_cursor_line->prev->next = tmtx->logical_cursor_line->next;

	free(tmtx->logical_cursor_line->arr);
	free(tmtx->logical_cursor_line);

	tmtx->logical_cursor_line = temp;
	tmtx->logical_cursor_row--;
	tmtx->logical_cursor_col = prev_line_length;
}

// this method allocates memory!
Line *new_line() {
	Line *l = (Line *)malloc(sizeof(Line));
	l->next = l->prev = NULL;
	l->exp = 1;
	l->arr = (char *)malloc(sizeof(char) * BUF_SIZE);
	l->arr[0] = '\0';
	return l;
}


void init_tmatrix(TMatrix *tmtx) {
	tmtx->head = tmtx->logical_cursor_line = tmtx->tail = new_line();
	tmtx->logical_cursor_col = tmtx->logical_cursor_row = 0;
}

// clean up
void destroy_tmatrix(TMatrix *tmtx) {
	// free data structure
	Line *current = tmtx->head, *temp;
	while(current) {
		temp = current->next;
		free(current->arr);
		free(current);
		current = temp;
	}
}

void move_logical_cursor_up(TMatrix *tmtx) {
	if(tmtx->logical_cursor_line != tmtx->head) {
		tmtx->logical_cursor_line = tmtx->logical_cursor_line->prev;
		tmtx->logical_cursor_row--;
	}

	if(strlen(tmtx->logical_cursor_line->arr) < tmtx->logical_cursor_col) {
		tmtx->logical_cursor_col = strlen(tmtx->logical_cursor_line->arr);
	}
}
void move_logical_cursor_down(TMatrix *tmtx) {
	if(tmtx->logical_cursor_line->next) {
		tmtx->logical_cursor_line = tmtx->logical_cursor_line->next;
		tmtx->logical_cursor_row++;
	}

	if(strlen(tmtx->logical_cursor_line->arr) < tmtx->logical_cursor_col)
		tmtx->logical_cursor_col = strlen(tmtx->logical_cursor_line->arr);
}
void move_logical_cursor_left(TMatrix *tmtx) {
	if(tmtx->logical_cursor_col > 0)
		tmtx->logical_cursor_col--;
}
void move_logical_cursor_right(TMatrix *tmtx) {
	if(tmtx->logical_cursor_col < strlen(tmtx->logical_cursor_line->arr))
		tmtx->logical_cursor_col++;
}
