#ifndef GLOBAL_H_
#define GLOBAL_H_
#define MAXIDLEN 33
typedef char string[MAXIDLEN];
typedef enum token_types {
    BEGIN, END, READ, WRITE, ID, INTLITERAL,
    LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP,
    PLUSOP, MINUSOP, CONDITIONALOP, SCANEOF
} token;

typedef struct operator {
    enum op { PLUS, MINUS } operator;
} op_rec;

enum expr { IDEXPR, LITERALEXPR, TEMPEXPR };

typedef struct expression {
    enum expr kind;
    union {
        string name;
        int val;
    };
} expr_rec;

FILE *file;

token scanner(void);

extern char token_buffer[];

char *fileNameR;


#endif // GLOBAL_H_
