#ifndef GLOBAL_H_
#define GLOBAL_H_
#define MAXIDLEN 33

#include "stdbool.h"

typedef char string[MAXIDLEN];
typedef enum token_types {
    BEGIN, END, READ, WRITE, ID, INTLITERAL,//0,1,2,3,4,5
    LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP,//6,7,8,9,10
    PLUSOP, MINUSOP, CONDITIONALOP, SCANEOF, ERROR//11,12,13,14,15
} token;

typedef struct operator {
    enum op { PLUS, MINUS } operator;
} op_rec;

enum expr { IDEXPR, LITERALEXPR, TEMPEXPR, NONE };

typedef struct expression {
    enum expr kind;
    union {
        string name;
        int val;
    };
} expr_rec;

FILE *file;

token scanner();

extern char token_buffer[];

char *fileNameR;

int in_conditional;

int col;
int line;
bool compiled;

token current_token;

#endif // GLOBAL_H_
