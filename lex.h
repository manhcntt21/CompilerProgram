#ifndef LEX_H
#define LEX_H

#define MAX_IDENT_LEN 10
#define MAX_NUM_Len 6
typedef enum {//Các loại Token được sử dụng trong PL/0
	NONE=0, IDENT, NUMBER,
	BEGIN, CALL, CONST, DO,  ELSE, END, FOR, IF, ODD,
	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
	PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS, LEQ, GTR, GEQ, LPARENT, RPARENT, LBRACK, RBRACK, PERIOD, COMMA, SEMICOLON,  ASSIGN, PERCENT
} TokenType;
TokenType getToken();
extern char printProgram[300];
extern int line;
extern TokenType Token;
#endif
