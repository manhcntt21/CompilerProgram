#include <stdio.h>
#include "lex.h"
#include <string.h>
#include <ctype.h>
TokenType getToken();
TokenType Token;            //Token nhận dạng được
int Num;                    //Từ vựng khi Token là NUMBER
char Id[MAX_IDENT_LEN + 1]; //Từ vựng khi Token là IDENT

FILE *input;
int line = 1, length = 0, length_number = 0;
char ch = ' ';
const char *reservedWords[] = {"BEGIN", "CALL", "CONST", "DO", "ELSE", "END", "FOR", "IF", "ODD", "PROCEDURE", "PROGRAM", "THEN", "TO", "VAR", "WHILE"};
char printProgram[300];
int index1 = 0;

char getCh()
{

    ch = fgetc(input);
    if (ch != EOF)
    printf("%c", ch);
    ch = toupper(ch);
    if (ch != EOF)
    {
        //  printf("%c",ch);
    }

    if (ch == '\n')
    {
        line++;
    }
    return ch;
}

TokenType getToken()
{   
    while (ch == ' ' || ch == '\n' || ch == '\t')
    {
        ch = getCh();
        if (ch == EOF)
            return NONE;
    }
    if (isalpha(ch))
    {
        length = 0;
        while (isalpha(ch) || isdigit(ch))
        {
            Id[length] = ch;
            length++;
            ch = getCh();
        }
        Id[length] = '\0';
        if (length > MAX_IDENT_LEN)
        {
            printf("line %d : Ident too long!\n", line);
            length = MAX_IDENT_LEN;
            Id[MAX_IDENT_LEN] = '\0';
        }
        if (length > 0)
        {
            int reservedSwitch = 15;
            for (int i = 0; i < 15; i++)
            {
                if (strcmp(Id, reservedWords[i]) == 0)
                {
                    reservedSwitch = i;
                    break;
                }
            }
            switch (reservedSwitch)
            {
            case 0:
                return BEGIN;
            case 1:
                return CALL;
            case 2:
                return CONST;
            case 3:
                return DO;
            case 4:
                return ELSE;
            case 5:
                return END;
            case 6:
                return FOR;
            case 7:
                return IF;
            case 8:
                return ODD;
            case 9:
                return PROCEDURE;
            case 10:
                return PROGRAM;
            case 11:
                return THEN;
            case 12:
                return TO;
            case 13:
                return VAR;
            case 14:
                return WHILE;
            default:
                return IDENT;
            }
        }
    }
    Num = 0;
    length_number = 0;
    if (isdigit(ch))
    {   
        fflush(stdin);
        Num = ch - 48;
        length_number++;
        ch = getCh();
        while (isdigit(ch))
        {
            if (length_number < MAX_NUM_Len)
            {
                Num = Num * 10 + ch - 48;
                ch = getCh();
                length_number++;
            }
            else
            {
                printf("line %d : number too large! \n", line);
                while (isdigit(ch))
                    ch = getCh();
                return NUMBER;
            }
        }
        return NUMBER;
    }
    if (ch == ':')
    {
        ch = getCh();
        if (ch == '=')
        {
            ch = getCh();
            return ASSIGN;
        }
        else
        {
            printf("line %d : letter not valid ", line);
            return NONE;
        }
    }
    else if (ch == '<')
    {
        ch = getCh();
        if (ch == '>')
        {
            ch = getCh();
            return NEQ;
        }
        else if (ch == '=')
        {
            ch = getCh();
            return LEQ;
        }
        else
        {
            return LSS;
        }
    }

    if (ch == '>')
    {
        ch = getCh();
        if (ch == '=')
        {
            ch = getCh();
            return GEQ;
        }
        else
        {
            return GTR;
        }
    }
    if (ch == '+')
    {
        ch = getCh();
        return PLUS;
    }
    else if (ch == '-')
    {
        ch = getCh();
        return MINUS;
    }
    else if (ch == '*')
    {
        ch = getCh();
        return TIMES;
    }
    else if (ch == '/')
    {
        ch = getCh();
        return SLASH;
    }
    else if (ch == '=')
    {
        ch = getCh();
        return EQU;
    }
    else if (ch == '(')
    {
        ch = getCh();
        return LPARENT;
    }
    else if (ch == ')')
    {
        ch = getCh();
        return RPARENT;
    }
    else if (ch == '[')
    {
        ch = getCh();
        return LBRACK;
    }
    else if (ch == ']')
    {
        ch = getCh();
        return RBRACK;
    }
    else if (ch == ';')
    {
        ch = getCh();
        return SEMICOLON;
    }
    else if (ch == ',')
    {
        ch = getCh();
        return COMMA;
    }
    else if (ch == '.')
    {
        ch = getCh();
        return PERIOD;
    }
    else if (ch == '%')
    {
        ch = getCh();
        return PERCENT;
    }
    else
        return NONE;
}
