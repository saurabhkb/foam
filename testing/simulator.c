// simulates performing the key strokes as indicated in the specified file
#include <stdio.h>
#include <stdlib.h>
#include "../editor.h"

#define BUF_LEN	100
#define MAX	10

typedef enum {
	LOAD, INSSTR, BP, INSNL, MVCRSR, MVCRSRUP, MVCRSRDN, MVCRSRRT, MVCRSRLFT, INVALID
} Op;

typedef union Arg {
	char str[MAX];
	int num1;
	int num2;
} Arg;

typedef struct Command {
	Op op;
	Arg arg;
} Command;

// parse commands from file and put into array
int parse_file(char *filename, Command commands[]) {
	char buf[BUF_LEN];
	char *piece1, *piece2, *piece3;
	int i = 0;
	FILE *f = fopen(filename, "r");
	// I assume that BUF_LEN (100) is sufficient to hold the line
	while(fgets(buf, BUF_LEN, f)) {
		if(buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = '\0';
		piece1 = strtok(buf, " ");
		if(!piece1)
			continue;
		if(piece1[0] == '#')
			continue;
		commands[i].op = INVALID;
		if(strcmp(piece1, "LOAD") == 0) commands[i].op = LOAD;
		if(strcmp(piece1, "INSSTR") == 0) commands[i].op = INSSTR;
		if(strcmp(piece1, "MVCRSR") == 0) commands[i].op = MVCRSR;
		if(strcmp(piece1, "MVCRSRUP") == 0) commands[i].op = MVCRSRUP;
		if(strcmp(piece1, "MVCRSRDN") == 0) commands[i].op = MVCRSRDN;
		if(strcmp(piece1, "MVCRSRRT") == 0) commands[i].op = MVCRSRRT;
		if(strcmp(piece1, "MVCRSRLFT") == 0) commands[i].op = MVCRSRLFT;
		if(strcmp(piece1, "BP") == 0) commands[i].op = BP;
		if(strcmp(piece1, "INSNL") == 0) commands[i].op = INSNL;

		switch(commands[i].op) {
			case LOAD:
				piece2 = strtok(NULL, " ");
				strcpy(commands[i].arg.str, piece2);
				break;
			case INSSTR:
				piece2 = strtok(NULL, " ");
				strcpy(commands[i].arg.str, piece2);
				break;
			case MVCRSR:
				piece2 = strtok(NULL, " ");	// row
				piece3 = strtok(NULL, " ");	// col
				commands[i].arg.num1 = atoi(piece2);
				commands[i].arg.num2 = atoi(piece3);
				break;
			case BP:
			case INSNL:
			case MVCRSRUP:
			case MVCRSRDN:
			case MVCRSRRT:
			case MVCRSRLFT:
				break;
			default:
				break;
		}
		i++;
	}
	fclose(f);
	return i;
}

void insert_string(CMatrix *cmtx, char str[]) {
	int i;
	for(i = 0; str[i]; i++)
		insert_at_cursor(cmtx, str[i]);
}

void print_matrix(CMatrix *cmtx) {
	Line *current = cmtx->head;
	while(current) {
		printf("%s\n", current->arr);
		current = current->next;
	}
}

int main(int argc, char **argv) {
	int count, i = 0;
	CMatrix matrix;

	if(argc != 2) return 1;

	init_blank(&matrix);

	Command commands[MAX];
	count = parse_file(argv[1], commands);

	if(count > 0) {
		if(commands[i].op == LOAD) {
			init_from_file(&matrix, commands[i].arg.str);	
			i++;
		}
	}

	for(; i < count; i++) {
		switch(commands[i].op) {
			case INSSTR:
				insert_string(&matrix, commands[i].arg.str);
				break;
			case BP:
				delete_before_cursor(&matrix);
				break;
			case INSNL:
				insert_newline_at_cursor(&matrix);
				break;
			case MVCRSR:
				move_cursor_to(&matrix, commands[i].arg.num1, commands[i].arg.num2);
				break;
			case MVCRSRUP:
				move_cursor_up(&matrix);
				break;
			case MVCRSRDN:
				move_cursor_down(&matrix);
				break;
			case MVCRSRLFT:
				move_cursor_left(&matrix);
				break;
			case MVCRSRRT:
				move_cursor_right(&matrix);
				break;
			default:
				printf("Invalid command!\n");
				break;
		}
	}

	print_matrix(&matrix);
	printf("(%d, %d)\n", matrix.cursor_row, matrix.cursor_col);
	return 0;
}

