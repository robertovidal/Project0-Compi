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
    printf("There was an error with the char %c. Line: %i, Column: %i", c, line, col);
}

token scanner(){
    int in_char, c;
    clear_buffer();
    if (feof(file))
        return SCANEOF;
    while ((in_char = getc(file)) != EOF){
        col++;
        if(in_char == '\n'){
            line++;
            col = 0;
        }
        if(isspace(in_char))
            continue;
        else if (isalpha(in_char)){
            buffer_char(in_char);
            for(c = getc(file); isalnum(c) || c == '_'; c = getc(file)){
                buffer_char(c);
            }
            ungetc(c, file);
            return check_reserved();
        } else if(isdigit(in_char)){
            buffer_char(in_char);
            for(c = getc(file); isdigit(c); c = getc(file))
                buffer_char(c);
            ungetc(c, file);
            return INTLITERAL;
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
            c = getc(file);
            if (c == '='){
                return ASSIGNOP;
            }
            else {
                ungetc(c, file);
                lexical_error(in_char);
                return ERROR;
            }
        } else if(in_char == '-'){
            c = getc(file);
            if(c == '-'){
                do
                    in_char = getc(file);
                while(in_char != '\n');
            } else {
                ungetc(c, file);
                return MINUSOP;
            }
        } else{
            lexical_error(in_char);
            return ERROR;
        }
    }
}

void return_chars(int count){
    for(int i = 0; i < count; i++){
        ungetc(token_buffer[i], file);
    }
}
