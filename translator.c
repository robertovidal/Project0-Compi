#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "translator.h"
#include "parser.h"


int size_sym_table = 0;
string sym_table[1000];
string sym_table_func[1000];
string postFix = "_add";

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
            sprintf(exp, "%s%s", expr.name, postFix);
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

int actual_register = 0;
char *get_register(void) {
    static char registername[MAXIDLEN];
    strcpy(registername, "");
    if(actual_register == 12)
        actual_register = 0;
    actual_register++;
    sprintf(registername, "r%d", actual_register);
    return registername;
}

char *get_last_register(void) {
    static char registername[MAXIDLEN];
    strcpy(registername, "");
    sprintf(registername, "r%d", actual_register);
    return registername;
}
char *get_last_l1_register(void) {
    static char registername[MAXIDLEN];
    strcpy(registername, "");
    if (actual_register == 1)
        sprintf(registername, "r%d", 12);
    else
        sprintf(registername, "r%d", actual_register-1);
    return registername;
}

int max_function = 0;
char *get_function(void) {
    static char fname[MAXIDLEN];
    sprintf(fname, "FUNC%d", max_function);
    strcpy(sym_table_func[max_function], fname);
    max_function++;
    return fname;
}

void start(void) {
    FILE * fileA;
    fileA = fopen(fileNameR, "w");
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
    string address_var = "";
    string var_declaration = "";
    for(int i = 0; i < size_sym_table; i++){
        sprintf(address_var, "%s%s", sym_table[i], postFix);
        sprintf(var_declaration, "\n\n%s: .word %s_var", address_var, sym_table[i]);
        fputs(var_declaration, fileA);
    }
    fputs("\n\nTEMP: .word TEMP1", fileA);
    fputs("\n\nstring1: .word string_1", fileA);
    fputs("\n\nstring2: .word string_2", fileA);
    fputs("\n\n.data", fileA);
    for(int i = 0; i < size_sym_table; i++){
        sprintf(var_declaration, "\n\n%s_var: .word 0", sym_table[i]);
        fputs(var_declaration, fileA);
    }
    fputs("\n\nTEMP1: .word 0", fileA);
    fputs("\n\nstring_1: .asciz \"%i\\n\"", fileA);
    fputs("\n\nstring_2: .asciz \"%i\"", fileA);
    fclose(fileA);
}

void finish(void) {
    generate("pop", "{ip", "pc}", "");
    declare_variables();
}

void assign(expr_rec target, expr_rec source) {
    char * last_reg = get_last_l1_register();
    string register_target_addr = "";
    string register_target_addr2 = "";
    strcpy(register_target_addr, get_register());
    string target_addr = "";
    sprintf(target_addr, "%s%s", target.name, postFix);
    generate("ldr", register_target_addr, target_addr, "");
    sprintf(register_target_addr2, "[%s]", register_target_addr);
    generate("str", last_reg, register_target_addr2, "");
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
    string temp_save = "";
    string last_reg = "";
    expr_rec e_rec;

    e_rec.kind = TEMPEXPR;
    strcpy(e_rec.name, "TEMP");

    if(e1.kind == LITERALEXPR){
        if(e2.kind == LITERALEXPR){
            switch(op.operator){
            case PLUS:
                assemblyLiteralExp(e1.val + e2.val, get_register());
                break;
            default:
                assemblyLiteralExp(e1.val - e2.val, get_register());
                break;
            }
            strcpy(last_reg, get_last_register());
        } else {
            assemblyTempExp(e2.name, postFix);
            strcpy(last_reg, get_last_register());
            string register_value = "";
            strcpy(register_value, get_register());

            assemblyLiteralExp(e1.val, register_value);

            generate(extract_op(op), register_value, register_value, last_reg);
            strcpy(last_reg, get_last_register());
        }
    } else {
        if(e1.kind != TEMPEXPR){
            assemblyTempExp(e1.name, postFix);
            strcpy(last_reg, get_last_register());
        } else {
            assemblyTempExp(e_rec.name, "");
            strcpy(last_reg, get_last_register());
        }

        if(e2.kind == LITERALEXPR){
            assemblyLiteralExp(e2.val, get_register());
            generate(extract_op(op), get_last_register(), last_reg, get_last_register());
        } else {
            assemblyTempExp(e2.name, postFix);
            generate(extract_op(op), get_last_register(), last_reg, get_last_register());
        }
        strcpy(last_reg, get_last_register());
    }

    generate("ldr", get_register(), e_rec.name, "");
    sprintf(temp_save, "[%s]", get_last_register());

    generate("str", last_reg, temp_save, "");
    return e_rec;
}

expr_rec single_expr_save(expr_rec e){
    string last_reg = "";

    single_expr(e);
    strcpy(last_reg, get_last_register());

    return save_temp(last_reg);
}

expr_rec save_temp(string last_reg){
    string temp_save = "";
    expr_rec e_rec;

    e_rec.kind = TEMPEXPR;
    strcpy(e_rec.name, "TEMP");

    generate("ldr", get_register(), e_rec.name, "");
    sprintf(temp_save, "[%s]", get_last_register());

    generate("str", last_reg, temp_save, "");

    return e_rec;
}

char * gen_conditional_phase1(expr_rec e1){
    // naming functions
    static char f_e3[MAXIDLEN];
    strcpy(f_e3, get_function());
    string jump_f_e3 = "";
    sprintf(jump_f_e3, "beq %s", f_e3);
    strcat(f_e3, ":");

    string zero = "";
    strcpy(zero, get_register()); // register with value 0

    if(e1.kind == TEMPEXPR)
        assemblyTempExp(e1.name, "");
    else
        assemblyTempExp(e1.name, postFix);

    string condition = "";
    strcpy(condition, get_last_register());

    generate("eor", zero, zero, ""); // make register with value 0
    generate("cmp", zero, condition, ""); // cmp op1 == 0
    generate(jump_f_e3, "", "", ""); // jump op3 if e1 == 0

    return f_e3;
}

void single_expr(expr_rec e){
    if (e.kind == LITERALEXPR) {
        assemblyLiteralExp(e.val, get_register());
    } else {
        if(e.kind == TEMPEXPR)
            assemblyTempExp("TEMP", "");
        else
            assemblyTempExp(e.name, postFix);
    }
}

int last_reg_with_val;
char * gen_conditional_phase2(string f_e3){
    last_reg_with_val = actual_register - 1;
    static char f_end[MAXIDLEN];
    string jump_end = "";
    strcpy(f_end, get_function());
    sprintf(jump_end, "b %s", f_end);
    strcat(f_end, ":");

    generate(jump_end, "", "", ""); // inconditional jump to end function
    generate(f_e3, "", "", "");

    return f_end;
}

expr_rec gen_conditional_phase3(expr_rec e2, expr_rec e3, string f_end){
    expr_rec e_rec;

    e_rec.kind = TEMPEXPR;
    strcpy(e_rec.name, "TEMP");

    // saves one load of TEMP
    if(actual_register - 1 != last_reg_with_val){
        string reg = "";
        sprintf(reg, "r%d", last_reg_with_val);
        generate("mov", reg, get_last_l1_register(), "");
        actual_register = last_reg_with_val + 1;
    }

    generate(f_end, "", "", ""); // end function
    return e_rec;
}

void assemblyLiteralExp(int val, string register_temp) {
    string res_str = "";
    sprintf(res_str, "#%d", val);
    generate("mov", register_temp, res_str, "");
}

void assemblyTempExp(string name, string postFix){
    string e_addr = "";
    string register_e_addr = "";
    string register_e_addr2 = "";
    string register_e = "";
    strcpy(register_e_addr, get_register());
    strcpy(register_e, get_register());
    sprintf(e_addr, "%s%s", name, postFix);
    generate("ldr", register_e_addr, e_addr, "");
    sprintf(register_e_addr2, "[%s]", register_e_addr);
    generate("ldr", register_e, register_e_addr2, "");
}

void read_id(expr_rec in_var) {
    generate("ldr", "r0", "string2", "");
    generate("ldr", "r1", extract_expr(in_var), "");
    generate("bl", "scanf", "", "");
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
    generate("ldr", "r2", extract_expr(out_expr), "");
    generate("ldr", "r1", "[r2]", "");
    generate("ldr", "r0", "string1", "");
    generate("bl", "printf", "", "");
}



