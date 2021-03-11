#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "global.h"


token current_token;

token next_tok;

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
}

void program(void){
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
    switch(tok){
    case ID:
        match(ID); match(ASSIGNOP);
        expression(); match(SEMICOLON);
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
    while(next_token() == COMMA){
        match(COMMA);
        match(ID);
    }
}

void expression(void){
    token t;
    primary();
    for(t = next_token(); t == PLUSOP || t == MINUSOP || t == CONDITIONALOP; t = next_token()){
        if(t == CONDITIONALOP){
            match(CONDITIONALOP);
            primary();
            match(CONDITIONALOP);
            primary();
        }
        else{
            add_op();
            primary();
        }
    }
}

void expr_list(void){
    expression();
    while(next_token() == COMMA){
        match(COMMA);
        expression();
    }
}

void add_op(void){
    token tok = next_token();
    if(tok == PLUSOP || tok == MINUSOP)
        match(tok);
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

void primary(void){
    token tok = next_token();
    switch(tok){
    case LPAREN:
        match(LPAREN); expression();
        match(RPAREN);
        break;
    case ID:
        match(ID);
        break;
    case INTLITERAL:
        match(INTLITERAL);
        break;
    default:
        error();
        break;
    }
}
