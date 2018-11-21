#include <stdio.h>
#include "lex.h"
extern char printProgram[300];
extern int line;

//function
void term(void);
void expression(void);
void factor(void);
void error(int errorCase, int line);
void condition(void);
void statement(void);
void block(void);
void program(void);

// term
void term()
{
    factor();
    // trong huong dan cua thay khong co PERCENT (%)
    while (Token == TIMES || Token == SLASH || Token == PERCENT)
    {
        Token = getToken();
        factor();
    }
}

//expression
void expression()
{
    if (Token == PLUS || Token == MINUS)
    {
        Token = getToken();
        term();
        while (Token == PLUS || Token == MINUS)
        {
            Token = getToken();
            term();
        }
    }
    term();
    while (Token == PLUS || Token == MINUS)
    {
        Token = getToken();
        term();
    }
}

// factor
void factor(void)
{
    if (Token == IDENT)
    {
        Token = getToken();
        if (Token == LBRACK)
        {
            Token = getToken();
            expression();
            if (Token == RBRACK)
            {
                Token = getToken();
            }
            else
            {
                // printf("\nFACTOR: IDENT: THIEU NGOAC VUONG");
                error(1, line);
            }
        }
    }
    if (Token == NUMBER)
    {
        Token = getToken();
    }
    if (Token == LPARENT)
    {
        expression();
        if (Token == RPARENT)
        {
            Token = getToken();
        }
        else
        {
            // printf("\nFACTOR: THIEU DAU DONG NGOAC");
            error(2, line);
        }
    }
}

//condition
void condition()
{
    if (Token == ODD)
    {
        Token = getToken();
        expression();
    }
    expression();
    if (Token == EQU || Token == LSS || Token == GTR ||
        Token == LEQ || Token == GEQ || Token == NEQ)
    {
        Token = getToken();
        expression();
    }
    else
    {
        // printf("\nCONDITION: SYNTAX ERROR");
        error(100, line);
    }
}

// statement
void statement()
{
    while (Token == IDENT || Token == CALL || Token == BEGIN || Token == IF || Token == WHILE || Token == FOR)
    {
        // ident
        if (Token == IDENT)
        {
            Token = getToken();
            if (Token == LBRACK)
            {
                Token = getToken();
                expression();
                if (Token == RBRACK)
                {
                    Token = getToken();
                }
                else
                {
                    //printf("\nSTATEMENT: IDENT: THIEU DAU DONG NGOAC VUONG");
                    error(1, line);
                }
            }
            if (Token == ASSIGN)
            {
                Token = getToken();
                expression();
            }
            else
            {
                // printf("\nSTATEMENT: IDENT: THIEU TOAN TU GAN");
                error(4, line);
            }
        }

        // Call
        if (Token == CALL)
        {
            Token = getToken();
            if (Token == IDENT)
            {
                Token = getToken();
                if (Token == LPARENT)
                {
                    Token = getToken();
                    expression();
                    while (Token == COMMA)
                    {
                        Token = getToken();
                        expression();
                    }
                    if (Token == RPARENT)
                    {
                        Token = getToken();
                    }
                    else
                    {
                        // printf("\nSTATEMENT: CALL: THIEU DAU DONG NGOAC DON");
                        error(2, line);
                    }
                }
            }
            else
            {
                // printf("\nSTATEMENT: CALL: THIEU TEN THU TUC HAM");
                error(5, line);
            }
        }

        // begin
        if (Token == BEGIN)
        {
            Token = getToken();
            statement();
            while (Token == SEMICOLON)
            {
                Token = getToken();
                statement();
            }
            if (Token == END)
            {
                Token = getToken();
            }
            else
            {
                // printf("\nSTATEMENT: BEGIN: THIEU TU KHOA END");
                error(6, line);
            }
        }
        // IF
        if (Token == IF)
        {
            Token = getToken();
            condition();
            if (Token == THEN)
            {
                Token = getToken();
                statement();
                if (Token == ELSE)
                {
                    Token = getToken();
                    statement();
                }
            }
            else
            {
                // printf("\nSTATEMENT: IF: THIEU TU KHOA THEN");
                error(7, line);
            }
        }

        // while
        if (Token == WHILE)
        {
            Token = getToken();
            condition();
            if (Token == DO)
            {
                Token = getToken();
                statement();
            }
            else
            {
                // printf("\nSTATEMENT: WHILE: THIEU TU KHOA DO");
                error(8, line);
            }
        }

        // FOR
        if (Token == FOR)
        {
            Token = getToken();
            if (Token == IDENT)
            {
                Token = getToken();
                if (Token == ASSIGN)
                {
                    Token = getToken();
                    expression();
                    if (Token == TO)
                    {
                        Token = getToken();
                        expression();
                        if (Token == DO)
                        {
                            Token = getToken();
                            statement();
                        }
                        else
                        {
                            // printf("\nSTATEMENT: FOR: THIEU TU KHOA DO");
                            error(8, line);
                        }
                    }
                    else
                    {
                        // printf("\nSTATEMENT: FOR: THIEU TU KHOA TO");
                        error(9, line);
                    }
                }
                else
                {
                    // printf("\nSTATEMENT: FOR: THIEU KI HIEU :=");
                    error(4, line);
                }
            }
            else
            {
                error(19, line);
            }
        }
    }
}
//block
void block(void)
{
    while (Token == CONST || Token == VAR || Token == PROCEDURE || Token == BEGIN)
    {
        // voi moi ham khong can doc gi truoc vi, mac dinh da doc truoc 1 ki tu roi
        while (Token == CONST)
        {
            do
            {
                Token = getToken();
                if (Token == IDENT)
                {
                    Token = getToken();
                    if (Token == ASSIGN)
                    {
                        Token = getToken();
                        if (Token == NUMBER)
                        {
                            Token = getToken();
                            if (Token == SEMICOLON)
                            {
                                Token = getToken();
                                break;
                            }
                            else if (Token != COMMA)
                            {
                                // thieu dau hai cham
                                error(12, line);
                            }
                        }
                        else
                        {
                            // printf("\nBLOCK: CONST: THIEU GIA TRI CUA BIEN\n");
                            error(11, line);
                        }
                    }
                    else
                    {
                        // printf("\nBLOCK: CONST: THIEU KI HIEU :=\n");
                        error(4, line);
                    }
                }
                else
                {
                    // thieu name const
                    error(17, line);
                }
            } while (Token == COMMA);
        }

        // var
        if (Token == VAR)
        {
            do
            {
                Token = getToken();
                if (Token == IDENT)
                {
                    Token = getToken();
                    if (Token == LBRACK)
                    {
                        Token = getToken();
                        if (Token == NUMBER)
                        {
                            Token = getToken();
                            if (Token == RBRACK)
                            {
                                Token = getToken();
                                if (Token == SEMICOLON)
                                {
                                    Token = getToken();
                                    break;
                                }
                            }
                            else
                            {
                                // printf("\nBLOCK: VAR: THIEU DAU DONG NGOAC\n");
                                error(1, line);
                            }
                        }
                        else
                        {
                            // printf("\nBLOCK: VAR: THIEU GIA TRI CUA MANG\n");
                            error(18, line);
                        }
                    }
                    if (Token == SEMICOLON)
                    {
                        Token = getToken();
                        break;
                    }
                    else if (Token != COMMA)
                    {
                        error(12, line);
                    }
                }
            } while (Token == COMMA);
        }
        // procedure
        if (Token == PROCEDURE)
        {
            Token = getToken();
            if (Token == IDENT)
            {
                Token = getToken();
                if (Token == LPARENT)
                {
                    do
                    {
                        Token = getToken();
                        if (Token == VAR)
                            Token = getToken();
                        if (Token == IDENT)
                        {
                            Token = getToken();
                            if (Token == RPARENT)
                            {
                                Token = getToken();
                                break;
                            }
                            else if (Token == SEMICOLON)
                            {
                            }
                            else
                            {
                                // printf("\nBLOCK: PROCEDURE: THIEU DAU DONG NGOAC DON\n");
                                error(2, line);
                            }
                        }
                    } while (Token == SEMICOLON);
                }
                if (Token == SEMICOLON)
                {
                    Token = getToken();
                    block();
                    if (Token == SEMICOLON)
                    {
                        Token = getToken();
                    }
                    else
                    {
                        // printf("\nBLOCK: PROCEDURE: THIEU DAU CHAM PHAY");
                        error(12, line);
                    }
                }
                else
                {
                    // printf("\nBLOCK: PROCEDURE: THIEU DAU CHAM PHAY");
                    error(12, line);
                }
            }
            else
            { // name procedure
                error(20, line);
            }
        }

        //begin
        if (Token == BEGIN)
        {
            Token = getToken();
            statement();
            while (Token == SEMICOLON)
            {
                Token = getToken();
                statement();
            }
            if (Token == END)
            {
                Token = getToken();
                break;
            }
            else
            {
                // printf("\nBLOCK: PROCEDURE: THIEU TU KHOA END");
                error(13, line);
            }
        }
    }
    // // vao block nhung khong nhay vao nhanh nao ca
    // if (Token == PERIOD)
    // {
    // }
    // else if (Token != CONST && Token != VAR && Token != PROCEDURE && Token != BEGIN && Token != NONE)
    // {
    //     error(100, line);
    // }
}

//program
void program(void)
{
    if (Token == PROGRAM)
    {
        Token = getToken();
        if (Token == IDENT)
        {
            Token = getToken();
            if (Token == SEMICOLON)
            {
                Token = getToken();
                block();
                if (Token == PERIOD)
                {
                    // khong loi, in ra chuong trinh
                    error(0, 0);
                }
                else
                {
                    // printf("\nTHIEU KY TU PRIOR");
                    error(14, line);
                }
            }
            else
            {
                // printf("\nPROGRAM: THIEU DAU CHAM PHAY");
                error(12, line);
            }
        }
        else
        {
            // printf("\nPROGRAM: THIEU IDENT");
            error(16, line);
        }
    }
    else
    {
        // printf("\nPROGRAM: THIEU PROGRAM");
        error(3, line);
    }
}

// error
void error(int errorCase, int line)
{

    switch (errorCase)
    {
    case 0:
        printf("%s\n", printProgram);
        printf("COMPILER SUCCESSFUL");
        break;
    case 1:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 1:");
        printf("MISSING RIGHT BRACKET\n"); // dong ngoac vuong
        break;
    case 2:
        printf("%s\n", printProgram);
        printf("Line: %d", line);
        printf("Errorr 2:");
        printf("MISSING RIGHT PARENTHESIS\n"); // dong ngoc tron
        break;
    case 3:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 3:");
        printf("MISSING PROGRAM\n");
        break;
    case 4:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 4:");
        printf("MISSING OPERATION ASSIGN\n");
        break;
    case 5:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 5:");
        printf("MISSING NAME FUNCTION (CALL)\n");
        break;
    case 6:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 6:");
        printf("MISSING RESERVED WORD END\n");
        break;
    case 7:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 7:");
        printf("MISSING RESERVED WORD THEN\n");
        break;
    case 8:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 8:");
        printf("MISSING RESERVED WORD DO\n");
        break;
    case 9:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 9:");
        printf("MISSING RESERVED WORD TO\n");
        break;
    case 10:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 10:");
        printf("MISSING OPERATION ASSIGN\n");
        break;
    case 11:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 11:");
        printf("MISSING VALUED CONST\n");
        break;
    case 12:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 12:");
        printf("MISSING SEMICOLON\n");
        break;
    case 13:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 13:");
        printf("MISSING RESERVED WORD END\n");
        break;
    case 14:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 14:");
        printf("MISSING PERIOD\n");
        break;
    case 15:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 15:");
        printf("MISSING OPERATION ASSIGN\n");
        break;
    case 16:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 16:");
        printf("MISSING NAME PROGRAMING\n");
        break;
    case 17:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 17:");
        printf("MISSING NAME CONST\n");
        break;
    case 18:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 18:");
        printf("MISSING VALUED IDENT VAR (KICH THUOC CUA MANG)\n");
        break;
    case 19:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 19:");
        printf("MISSING  IDENT IN FOR\n");
        break;
    case 20:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr 20:");
        printf("MISSING  NAME PROCEDURE\n");
        break;
    default:
        printf("%s\n", printProgram);
        printf("Line: %d ", line);
        printf("Errorr :");
        printf("SYNTAX ERROR\n");
        break;
    }
}
// void main() {

// }

// gcc *.c
// pl0 A2

// in ra chuong trinh neu, chunog trinh thanh cong, neu loi in den cho loi

// toi chu nhat nop.