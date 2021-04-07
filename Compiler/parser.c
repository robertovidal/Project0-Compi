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
    printf("There was an error in line: %i, Column: %i \n", line, col);
}

void match(token tok){
    current_token = next_tok;
    if(current_token != SCANEOF){
        next_tok = scanner();
        strcpy(current_buffer, next_buffer);
        strcpy(next_buffer, token_buffer);
        strcpy(token_buffer, current_buffer);
    }
    if(current_token != tok){
        printf("Current token (%i) different than token asked (%i) \n", current_token, tok);
        error();
    }
}

void system_goal(void){
    col = 0;
    line = 0;
    next_tok = scanner();
    strcpy(next_buffer, token_buffer);
    program();
    match(SCANEOF);
    finish();
}

void program(void){
    start();
    match(BEGIN);
    statement_list();
    match(END);
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
        match(ID);
        target = process_id();
        match(ASSIGNOP);
        expression(&source, NOSKIP);
        match(SEMICOLON);
        assign(target, source);
        break;
    case READ:
        match(READ); match(LPAREN);
        id_list(); match(RPAREN);
        match(SEMICOLON);
        break;
    case WRITE:
        match(WRITE); match(LPAREN);
        expr_list(); match(RPAREN);
        match(SEMICOLON);
        break;
    default:
        printf("statement token not found (%i)", tok);
        error();
        break;
    }
}

void id_list(void){
    match(ID);
    expr_rec id = process_id();
    read_id(id);
    while(next_token() == COMMA){
        match(COMMA);
        match(ID);
        expr_rec id = process_id();
        read_id(id);
    }
}


void expression(expr_rec *result, skip skip) {
    token t;
    expr_rec left_operand, center_operand, right_operand;
    right_operand.kind = NONE;
    center_operand.kind = NONE;
    left_operand.kind = NONE;
    op_rec op;
    primary(& left_operand);
    for(t = next_token(); t == PLUSOP || t == MINUSOP || t == CONDITIONALOP; t = next_token()){
        if(t == CONDITIONALOP){
            if(skip == CONDITIONAL || skip == CONDITIONAL_SAVE)
                break;
            match(CONDITIONALOP);

            if(left_operand.kind == LITERALEXPR){
                if (left_operand.val){
                    expression(& center_operand, CONDITIONAL);
                    match(CONDITIONALOP);
                    expression(& right_operand, CONDITIONAL_SAVE);
                    left_operand = center_operand;
                } else {
                    expression(& center_operand, CONDITIONAL_SAVE);
                    match(CONDITIONALOP);
                    expression(& right_operand, NOSKIP);
                    left_operand = right_operand;
                }
                break;
            } else {
                string f_e3 = "";
                strcpy(f_e3, gen_conditional_phase1(left_operand));
                expression(& center_operand, CONDITIONAL);
                string f_end = "";
                strcpy(f_end, gen_conditional_phase2(f_e3));
                match(CONDITIONALOP);
                expression(& right_operand, NOSKIP);
                left_operand = gen_conditional_phase3(center_operand, right_operand, f_end);
            }
        } else if(t == PLUSOP || t == MINUSOP){
            add_op(& op);
            primary(& right_operand);
            if(skip != CONDITIONAL_SAVE)
                left_operand = gen_infix(left_operand, op, right_operand);
        }
    }
    if(right_operand.kind == NONE && center_operand.kind == NONE && left_operand.kind != NONE && skip != CONDITIONAL_SAVE){
        single_expr_save(left_operand);
    }
    *result = left_operand;
}

void expr_list(void){
    expr_rec expr;
    expression(&expr, NOSKIP);
    write_expr(expr);
    while(next_token() == COMMA){
        match(COMMA);
        expression(&expr, NOSKIP);
        write_expr(expr);
    }
}

void add_op(op_rec *result){
    token tok = next_token();
    if(tok == PLUSOP || tok == MINUSOP){
        match(tok);
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
        match(LPAREN); expression(&res, NOSKIP);
        match(RPAREN);
        *result = res;
        break;
    case ID:
        match(ID);
        *result = process_id();
        break;
    case INTLITERAL:
        match(INTLITERAL);
        *result = process_literal();
        break;
    default:
    printf("primary token not found (%i)", tok);
        error();
        break;
    }
}
