#ifndef GLOBAL_H_
#define GLOBAL_H_
typedef enum token_types {
    BEGIN, END, READ, WRITE, ID, INTLITERAL,
    LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP,
    PLUSOP, MINUSOP, CONDITIONALOP, SCANEOF
} token;

FILE *file;

token scanner(void);

extern char token_buffer[];

token token_list[100];

char *fileNameR;


#endif // GLOBAL_H_
