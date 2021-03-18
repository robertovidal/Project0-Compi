#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "translator.h"
#include "parser.h"


int size_sym_table = 0;
string sym_table[MAXIDLEN];

extern int lookup(string s);

extern void enter(string s);

void generate(char *op_code, char *a, char *b, char *r) {
    // pone instrucción correcta en archivo
    FILE * fileA;
    char res[1000] = "\n\t";

    fileA = fopen(fileNameR, "a");
    if(fileA == NULL) {
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
        strcat(res, ", ");
        strcat(res, b);
    }
    if (strlen(r) > 0) {
        strcat(res, ", ");
        strcat(res, r);
    }
    fputs(res, fileA);
    fclose(fileA);
}

char * extract_op(op_rec op) {
    switch(op.operator){
        case PLUS:
            return "add";
        case MINUS:
            return "sub";
        default:
            return "";
        }
}

char * extract_expr(expr_rec expr) {
    static string exp = "";
    switch(expr.kind){
        case IDEXPR:
        case TEMPEXPR:
            strcpy(exp, expr.name);
            return exp;
        case LITERALEXPR:
            sprintf(exp, "#%d", expr.val);
            return exp;
        default:
            return "";
        }
}

int lookup(string s) {
    for(int i = 0; i < size_sym_table; i++){
        if(!strcmp(sym_table[i], s)){
            return 1;
        }
    }
    return 0;
}

void enter(string s) {
    strcpy(sym_table[size_sym_table], s);
    size_sym_table++;
}

void check_id(string s) {
    if (!lookup(s)) {
        enter(s);
    }
}

int actual_register = 1;
char *get_register(void) {
    static char registername[MAXIDLEN];
    strcpy(registername, "");
    if(actual_register == 12)
        actual_register = 1;
    actual_register++;
    sprintf(registername, "r%d", actual_register);
    return registername;
}

int max_temp = 0;
char *get_temp(void) {
    static char tempname[MAXIDLEN];
    max_temp++;
    sprintf(tempname, "TEMP%d", max_temp);
    check_id(tempname);
    return tempname;
}

void start(void) {
    FILE * fileA;
    fileA = fopen(fileNameR, "a");
    if(fileA == NULL) {
        printf("No se pudo editar el archivo.\n");
        exit(EXIT_FAILURE);
    }
    char res[] = ".section .text\n.global main\n.extern printf\n\nmain:";
    fputs(res, fileA);
    fclose(fileA);
    generate("push", "{ip", "lr}", "");
}

void declare_variables(void){
    FILE * fileA;
    fileA = fopen(fileNameR, "a");
    if(fileA == NULL) {
        printf("No se pudo editar el archivo.\n");
        exit(EXIT_FAILURE);
    }
    char line[2000] = "";
    string address_var = "";
    string var_declaration = "";
    for(int i = 0; i < size_sym_table; i++){
        sprintf(address_var, "%s_address", sym_table[i]);
        sprintf(var_declaration, "\n\n%s: .word %s", address_var, sym_table[i]);
        strcat(line, var_declaration);
    }
    strcat(line, "\n\n.data");
    for(int i = 0; i < size_sym_table; i++){
        sprintf(var_declaration, "\n\n%s: .word 0", sym_table[i]);
        strcat(line, var_declaration);
    }
    fputs(line, fileA);
    fclose(fileA);
}

void finish(void) {
    generate("pop", "{ip", "pc}", "");
    declare_variables();
}

void assign(expr_rec target, expr_rec source) {
    string register_target_addr = "";
    string register_target_addr2 = "";
    string register_source = "";
    strcpy(register_target_addr, get_register());
    strcpy(register_source, get_register());
    string target_addr = "";
    sprintf(target_addr, "%s_address", target.name);
    generate("ldr", register_target_addr, target_addr, "");
    sprintf(register_target_addr2, "[%s]", register_target_addr);
    if(source.kind == LITERALEXPR){
        generate("mov", register_source, extract_expr(source), "");
    }else{
        string register_source_addr = "";
        string register_source_addr2 = "";
        strcpy(register_source_addr, get_register());
        string source_addr = "";
        sprintf(source_addr, "%s_address", source.name);
        generate("ldr", register_source_addr, source_addr, "");
        sprintf(register_source_addr2, "[%s]", register_source_addr);
        generate("ldr", register_source, register_source_addr2, "");
    }
    generate("str", register_source, register_target_addr2, "");
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
    string register_temp_addr = "";
    string register_temp_addr2 = "";
    string register_temp = "";
    strcpy(register_temp_addr, get_register());
    strcpy(register_temp, get_register());
    string temp_addr = "";
    sprintf(temp_addr, "%s_address", e_rec.name);
    generate("ldr", register_temp_addr, temp_addr, "");
    sprintf(register_temp_addr2, "[%s]", register_temp_addr);
    if(e1.kind == LITERALEXPR){
        if(e2.kind == LITERALEXPR){
            int res;
            string res_str = "";
            switch(op.operator){
            case PLUS:
                res = e1.val + e2.val;
                break;
            default:
                res = e1.val - e2.val;
                break;
            }
            sprintf(res_str, "#%d", res);
            generate("mov", register_temp, res_str, "");
        } else {
            string register_e2_addr = "";
            string register_e2_addr2 = "";
            string register_e2 = "";
            strcpy(register_e2_addr, get_register());
            strcpy(register_e2, get_register());
            string e2_addr = "";
            sprintf(e2_addr, "%s_address", e2.name);
            generate("ldr", register_e2_addr, e2_addr, "");
            sprintf(register_e2_addr2, "[%s]", register_e2_addr);
            generate("ldr", register_e2, register_e2_addr2, "");
            string register_value = "";
            string string_value = "";
            strcpy(register_value, get_register());
            sprintf(string_value, "#%d", e1.val);
            generate("mov", register_value, string_value, "");
            generate(extract_op(op), register_temp, register_value, register_e2);
        }
    } else{
        string register_e1_addr = "";
        string register_e1_addr2 = "";
        string register_e1 = "";
        strcpy(register_e1_addr, get_register());
        strcpy(register_e1, get_register());
        string e1_addr = "";
        sprintf(e1_addr, "%s_address", e1.name);
        generate("ldr", register_e1_addr, e1_addr, "");
        sprintf(register_e1_addr2, "[%s]", register_e1_addr);
        generate("ldr", register_e1, register_e1_addr2, "");
        if(e2.kind == LITERALEXPR){
            generate(extract_op(op), register_temp, register_e1, extract_expr(e2));
        }
        else{
            string register_e2_addr = "";
            string register_e2_addr2 = "";
            string register_e2 = "";
            strcpy(register_e2_addr, get_register());
            strcpy(register_e2, get_register());
            string e2_addr = "";
            sprintf(e2_addr, "%s_address", e2.name);
            generate("ldr", register_e2_addr, e2_addr, "");
            sprintf(register_e2_addr2, "[%s]", register_e2_addr);
            generate("ldr", register_e2, register_e2_addr2, "");
            generate(extract_op(op), register_temp, register_e1, register_e2);
        }
    }
    generate("str", register_temp, register_temp_addr2, "");
    return e_rec;
}

void read_id(expr_rec in_var) {
    generate("Read", in_var.name, "Integer", "");
}

expr_rec process_id(void) {
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



