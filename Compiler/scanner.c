#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "global.h"
#include "scanner.h"

char token_buffer[100] = "";

void clear_buffer(void){
    strcpy(token_buffer, "");
}

void buffer_char(char c){
    size_t buffer_length = strlen(token_buffer);
    token_buffer[buffer_length] = c;
    token_buffer[buffer_length + 1] = '\0';
}

token check_reserved(void){
    if(strcmp(token_buffer,"begin") == 0){
        return BEGIN;
    } else if (strcmp(token_buffer,"end") == 0){
        return END;
    } else if (strcmp(token_buffer,"read") == 0){
        return READ;
    } else if (strcmp(token_buffer,"write") == 0){
        return WRITE;
    } else if (strcmp(token_buffer,"SCANEOF") == 0){
        return SCANEOF;
    }
    else{
        return ID;
    }

}

void lexical_error(char c){
    compiled = false;
    printf("There was an error with the char %c. Line: %i, Column: %i \n", c, line, col);
}

token scanner(){
    int in_char, c;
    clear_buffer();
    if (feof(file))
        return SCANEOF;
    while ((in_char = getChar()) != EOF){
        if(isspace(in_char))
            continue;
        else if (isalpha(in_char)){
            buffer_char(in_char);
            for(c = getChar(); isalnum(c) || c == '_'; c = getChar()){
                buffer_char(c);
            }
            ungetc(c, file);
            return check_reserved();
        } else if(isdigit(in_char)){
            return storeLiteral(in_char);
        } else if(in_char == '('){
            return LPAREN;
        } else if(in_char == ')'){
            return RPAREN;
        } else if(in_char == ';'){
            return SEMICOLON;
        } else if(in_char == ','){
            return COMMA;
        } else if(in_char == '+'){
            return PLUSOP;
        } else if(in_char == '|'){
            return CONDITIONALOP;
        }else if(in_char == ':'){
            c = getChar();
            if (c == '='){
                return ASSIGNOP;
            }
            else {
                ungetc(c, file);
                lexical_error(in_char);
                return ERROR;
            }
        } else if(in_char == '-'){
            c = getChar();
            if(c == '-'){
                do
                    in_char = getChar();
                while(in_char != '\n');
                line++;
                col = 1;
            } else {
                if(current_token != ASSIGNOP && current_token != PLUSOP && 
                current_token != LPAREN && current_token != CONDITIONALOP){
                    ungetc(c, file);
                    return MINUSOP;
                } else {
                    buffer_char(in_char);
                    do{
                        if(isspace(c)){
                            continue;
                        }else if(isdigit(c)){
                            return storeLiteral(c);
                        } else {
                            lexical_error(in_char);
                            return ERROR;
                        }
                        c = getChar();
                    }while(c != '\n');
                }
            }
        } else{
            lexical_error(in_char);
            return ERROR;
        }
    }
}

token storeLiteral(char c){
    int count = 0;
    buffer_char(c);
    for(c = getChar(); isdigit(c); c = getChar()){
        count++;
        buffer_char(c);
    }
    ungetc(c, file);
    if(count >= 32)
        return ERROR;
    return INTLITERAL;
}

char getChar(){
    char c = getc(file);
    col++;
    if(c == '\n'){
        line++;
        col = 1;
    }
    return c;
}
