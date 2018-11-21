#include "lex.h"
#include "parSyntax.h"
#include <stdio.h>

extern FILE *input;
extern TokenType Token;
extern char Id[MAX_IDENT_LEN + 1];
extern int Num;
FILE *f; // lexioutput.txt
char TokenTable[][15] = {
    "NONE", "IDENT", "NUMBER",
    "BEGIN", "CALL", "CONST", "DO", "ELSE", "END", "FOR", "IF", "ODD",
    "PROCEDURE", "PROGRAM", "THEN", "TO", "VAR", "WHILE",
    "PLUS", "MINUS", "TIMES", "SLASH", "EQU", "NEQ", "LSS", "LEQ", "GTR", "GEQ", "LPARENT", "RPARENT", "LBRACK", "RBRACK", "PERIOD", "COMMA", "SEMICOLON", "ASSIGN", "PERCENT"};

void main(char argc, char *argv[])
{
    if (argc < 2)
    {
        input = fopen("Example.pl0", "rt");
//        f = fopen("/home/manh/PhuongPhapDich/baitapolop/BTL/lexicaloutput.txt", "w");
    }
    else if (argc == 2)
    {
        input = fopen(argv[1], "rt");
        // f = open("lexout1.txt", "w");
    }
    else
    {
        printf("Erorr File");
    }
//    if (!f)
//    {
//        printf("OPEN FILE IS FAILED");
//    }

// qua trinh phan tich tu vung va ghi vao file (chua biet cach tach ra doc lap)
//     do
//     {
//         Token = getToken();
//         if (Token == IDENT)
//         {
//             printf("%-15s(%s)\n", TokenTable[Token], Id);
//             fprintf(f, "%-15s(%s)\n", TokenTable[Token], Id);
//             //             fputs(TokenTable[Token], f);
//             //             fputs(Id, f);
//             //             fputs("\n", f);
//         }
//         else if (Token == NUMBER)
//         {
//             printf("%-15s(%d)\n", TokenTable[Token], Num);
//             fprintf(f, "%-15s(%d)\n", TokenTable[Token], Num);
//             //             fputs(TokenTable[Token], f);
//             //             fputs(Num, f);
//             //             fputs("\n", f);
//         }
//         else
//         {
//             printf("%-15s\n", TokenTable[Token]);
//             fprintf(f, "%-15s\n", TokenTable[Token]);
//             //            fputs(TokenTable[Token],f);
//             //            fputs("\n",f);
//         }
//     } while (Token != NONE);
//    rewind(f); // dua file ve dau, vi qua trinh phan tich tu vung file khong o dau
    printf("\n---------------------------PHAN TICH CU PHAP---------------------------------\n");
    Token = getToken();
    program();
    printf("%s", printProgram);
//    fclose(f);
    fclose(input);
}
