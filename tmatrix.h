#ifndef __TMATRIX
#define __TMATRIX

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE	20	// read buffer size

typedef struct Line {
	char *arr;
	int exp;	// stores the power of 2 currently reached for realloc
	struct Line *next;
	struct Line *prev;
} Line;

typedef struct {
	Line *head;
	Line *tail;
	Line *logical_cursor_line;
	int logical_cursor_row;
	int logical_cursor_col;
} TMatrix;


void insert(TMatrix *, int);
void delete(TMatrix *);
void insert_newline(TMatrix *);
void delete_newline(TMatrix *);

void move_logical_cursor_up(TMatrix *);
void move_logical_cursor_down(TMatrix *);
void move_logical_cursor_left(TMatrix *);
void move_logical_cursor_right(TMatrix *);

Line *new_line();

void init_tmatrix(TMatrix *);
void destroy_tmatrix(TMatrix *);

#endif
