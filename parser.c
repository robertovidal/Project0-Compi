#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "global.h"
#include "parser.h"
#include "translator.h"


char next_buffer[100];

char current_buffer[100];

token next_token(void){
    return next_tok;
}

void error(void){
    printf("There was an error \n");
}

void match(token tok, times again){
    current_token = next_tok;
    if(current_token != SCANEOF){
        next_tok = scanner(again);
        strcpy(current_buffer, next_buffer);
        strcpy(next_buffer, token_buffer);
        strcpy(token_buffer, current_buffer);
    }
    if(current_token != tok){
        printf("Current token (%i) different than token asked (%i) \n", current_token, tok);
        error();
    }
    else
        printf("nice (%i) with (%i)\n", current_token, tok);
}

void system_goal(void){
    next_tok = scanner(FIRST);
    strcpy(next_buffer, token_buffer);
    program();
    match(SCANEOF,FIRST);
    finish();
}

void program(void){
    start();
    match(BEGIN,FIRST);
    statement_list();
    match(END,FIRST);
}

void statement_list(void){
    statement();
    for(;;){
        switch(next_token()){
        case ID:
        case READ:
        case WRITE:
            statement();
            break;
        default:
            return;
        }
    }
}

void statement(void){
    token tok = next_token();
    expr_rec target, source;
    switch(tok){
    case ID:
        match(ID,FIRST);
        target = process_id();
        match(ASSIGNOP,FIRST);
        expression(&source, false);
        match(SEMICOLON,FIRST);
        assign(target, source);
        break;
    case READ:
        match(READ,FIRST); match(LPAREN,FIRST);
        id_list(); match(RPAREN,FIRST);
        match(SEMICOLON,FIRST);
        break;
    case WRITE:
        match(WRITE,FIRST); match(LPAREN,FIRST);
        expr_list(); match(RPAREN,FIRST);
        match(SEMICOLON,FIRST);
        break;
    default:
        printf("statement token not found (%i)", tok);
        error();
        break;
    }
}

void id_list(void){
    match(ID,FIRST);
    expr_rec id = process_id();
    read_id(id);
    while(next_token() == COMMA){
        match(COMMA,FIRST);
        match(ID,FIRST);
        expr_rec id = process_id();
        read_id(id);
    }
}

void expression(expr_rec *result, bool skip) {
    token t;
    expr_rec left_operand, center_operand, right_operand;
    right_operand.kind = NONE;
    center_operand.kind = NONE;
    left_operand.kind = NONE;
    op_rec op;
    primary(& left_operand);
    for(t = next_token(); t == PLUSOP || t == MINUSOP || t == CONDITIONALOP; t = next_token()){
        if(t == CONDITIONALOP){
            if(skip)
                break;
            match(CONDITIONALOP, SECOND);
            //primary(& center_operand); //next_token()
            //primary(& right_operand);
            //left_operand = gen_conditional(left_operand, center_operand, right_operand);

            if(left_operand.kind == LITERALEXPR){
                expression(& center_operand, true);
                match(CONDITIONALOP,SECOND);
                if (left_operand.val){
                    expression(& right_operand, true);
                    left_operand = single_expr_save(center_operand);
                } else {
                    expression(& right_operand, false);
                    left_operand = single_expr_save(right_operand);
                }
                break;
            } else {
                string f_e3 = "";
                strcpy(f_e3, gen_conditional_phase1(left_operand));
                expression(& center_operand, true);
                string f_end = "";
                strcpy(f_end, gen_conditional_phase2(f_e3));
                match(CONDITIONALOP,SECOND);
                expression(& right_operand, true);
                left_operand = gen_conditional_phase3(center_operand, right_operand, f_end);
            }
        } else if(t == PLUSOP || t == MINUSOP){
            add_op(& op);
            primary(& right_operand);
            left_operand = gen_infix(left_operand, op, right_operand);
        }
    }
    if(right_operand.kind == NONE && center_operand.kind == NONE && left_operand.kind != NONE && !skip){
        single_expr_save(left_operand);
    }
    *result = left_operand;
}

void expr_list(void){
    expr_rec expr;
    expression(&expr, false);
    write_expr(expr);
    while(next_token() == COMMA){
        match(COMMA,FIRST);
        expression(&expr, false);
        write_expr(expr);
    }
}

void add_op(op_rec *result){
    token tok = next_token();
    if(tok == PLUSOP || tok == MINUSOP){
        match(tok,FIRST);
        *result = process_op();
    }
    else
        error();
}

void primary(expr_rec *result){
    token tok = next_token();
    expr_rec res;
    switch(tok){
    case LPAREN:
        match(LPAREN,FIRST); expression(&res, false);
        match(RPAREN,FIRST);
        *result = res;
        break;
    case ID:
        match(ID,FIRST);
        *result = process_id();
        break;
    case INTLITERAL:
        match(INTLITERAL,FIRST);
        *result = process_literal();
        break;
    default:
    printf("primary token not found (%i)", tok);
        error();
        break;
    }
}
