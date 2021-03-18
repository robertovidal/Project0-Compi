#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "global.h"
#include "parser.h"


char next_buffer[100];

char current_buffer[100];

token next_token(void){
    return next_tok;
}

void error(void){
    printf("There was an error \n");
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
        error();
    }
    else
        printf("nice\n");
}

void system_goal(void){
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
        expression(&source);
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

void expression(expr_rec *result) {
    token t;
    expr_rec left_operand, center_operand, right_operand;
    op_rec op;
    primary(& left_operand);
    for(t = next_token(); t == PLUSOP || t == MINUSOP || t == CONDITIONALOP; t = next_token()){
        if(t == CONDITIONALOP){
            match(CONDITIONALOP);
            primary(& center_operand);
            match(CONDITIONALOP);
            primary(& right_operand);
        }
        else{
            add_op(& op);
            primary(& right_operand);
            left_operand = gen_infix(left_operand, op, right_operand);
        }
    }
    *result = left_operand;
}

void expr_list(void){
    expr_rec expr;
    expression(&expr);
    write_expr(expr);
    while(next_token() == COMMA){
        match(COMMA);
        expression(&expr);
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

void cond_op(void){
    token tok = next_token();
    if(tok == PLUSOP || tok == MINUSOP)
        match(tok);
    else
        error();
}

void primary(expr_rec *result){
    token tok = next_token();
    expr_rec res;
    switch(tok){
    case LPAREN:
        match(LPAREN); expression(&res);
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
        error();
        break;
    }
}
