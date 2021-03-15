#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "translator.h"
#include "parser.h"


int size_sym_table = 0;
char ** sym_table = NULL;


extern int lookup(string s);

extern void enter(string s);

void generate(string op_code, string a, string b, string r) {
    // pone instrucción correcta en archivo
    FILE * file;
    string res = "";

    file = fopen(fileNameR, "a");
    if(file == NULL) {
        printf("No se pudo editar el archivo.\n");
        exit(EXIT_FAILURE);
    }

    if (strlen(op_code) > 0) {
        strcat(res, op_code);
    }
    if (strlen(a) > 0) {
        strcat(res, " ");
        strcat(res, a);
    }
    if (strlen(b) > 0) {
        strcat(res, ",");
        strcat(res, b);
    }
    if (strlen(r) > 0) {
        strcat(res, ",");
        strcat(res, r);
    }

    fputs(res, file);
    fclose(file);
}

char * extract_op(op_rec op) {
    switch(op.operator){
        case PLUS:
            return "Add";
        case MINUS:
            return "Sub";
        default:
            return "";
        }
}

char * extract_expr(expr_rec expr) {
    char * exp = "";

    switch(expr.kind){
        case IDEXPR:
        case TEMPEXPR:
            strcpy(exp, expr.name);
            return exp;
        case LITERALEXPR:
            sprintf(exp, "%d", expr.val);
            return exp;
        default:
            return "";
        }
}

int lookup(string s) {
    for(int i = 0; i < size_sym_table; i++){
        if(strcmp(sym_table[i], s)){
            return 1;
        }
    }
    return 0;
}

void enter(string s) {
    if(size_sym_table % 30 == 0 || sym_table == NULL){
        sym_table = realloc(sym_table, 30 * sizeof(string));
    }
    sym_table[size_sym_table] = s;
    size_sym_table++;
}

void check_id(string s) {
    if (!lookup(s)) {
        enter(s);
        generate("Declare", s, "Integer", "");
    }
}

char *get_temp(void) {
    static int max_temp = 0;
    static char tempname[MAXIDLEN];

    max_temp++;
    sprintf(tempname, "Temp&%d", max_temp);
    check_id(tempname);
    return tempname;
}

void start(void) {

}

void finish(void) {
    generate("Halt", "", "", "");
}

void assign(expr_rec target, expr_rec source) {
    generate("Store", extract_expr(source), target.name, "");
}

op_rec process_op(void) {
    op_rec o;

    if (current_token == PLUSOP)
        o.operator = PLUS;
    else
        o.operator = MINUS;
    
    return o;
}

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2) {
    expr_rec e_rec;

    e_rec.kind = TEMPEXPR;

    strcpy(e_rec.name, get_temp());
    generate(extract_op(op), extract_expr(e1), extract_expr(e2), e_rec.name);

    return e_rec;
}

void read_id(expr_rec in_var) {
    generate("Read", in_var.name, "Integer", "");
}

expr_rec process_id(expr_rec in_var) {
    expr_rec t;

    check_id(token_buffer);
    t.kind = IDEXPR;
    strcpy(t.name, token_buffer);

    return t;
}

expr_rec process_literal(void) {
    expr_rec t;
    
    t.kind = LITERALEXPR;
    (void) sscanf(token_buffer, "%d", & t.val);

    return t;
}

void write_expr(expr_rec out_expr) {
    generate("Write", extract_expr(out_expr), "Integer", "");
}

/* Creo que va en el parser

void expression(expr_rec *result) {
    expr_rec left_operand, right_operand;
    op_rec op;

    primary(& left_operand);
    while(next_token() == PLUSOP || next_token() == MINUSOP) {
        add_op(& op);
        primary(& right_operand);
        left_operand = gen_infix(left_operand, op, right_operand);
    }

    *result = left_operand;
}

*/