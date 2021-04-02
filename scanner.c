#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "global.h"
#include "scanner.h"

char token_buffer[100] = "";
int col = 0;
int line = 0;

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
        printf("BEGIN\n");
        return BEGIN;
    } else if (strcmp(token_buffer,"end") == 0){
        printf("END\n");
        return END;
    } else if (strcmp(token_buffer,"read") == 0){
        printf("READ\n");
        return READ;
    } else if (strcmp(token_buffer,"write") == 0){
        printf("WRITE\n");
        return WRITE;
    } else if (strcmp(token_buffer,"SCANEOF") == 0){
        printf("SCANEOF\n");
        return SCANEOF;
    }
    else{
        printf("ID\n");
        return ID;
    }

}

void lexical_error(char c){
    printf("There was an error with the char %c. Line: %i, Column: %i", c, line, col);
}

token scanner(times again){
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
            printf("INTLITERAL\n");
            return INTLITERAL;
        } else if(in_char == '('){
            printf("LPAREN\n");
            return LPAREN;
        } else if(in_char == ')'){
            printf("RPAREN\n");
            return RPAREN;
        } else if(in_char == ';'){
            printf("SEMICOLON\n");
            return SEMICOLON;
        } else if(in_char == ','){
            printf("COMMA\n");
            return COMMA;
        } else if(in_char == '+'){
            printf("PLUSOP\n");
            return PLUSOP;
        } else if(in_char == '|'){
            printf("line: %i, col: %i \n", line, col);
            printf("AGAIN: %d \n",again);
            printf("CHAR: %d \n",in_char);
            // int count = 0;
            // int count_all = 0;
            // if(again == FIRST){
            //     for(c = getc(file); c != '|'; c = getc(file)){
            //         count_all++;
            //         buffer_char(c);
            //         if(isspace(in_char))
            //             continue;
            //         if(c == ';'){
            //             printf("PUNTO Y COMA");
            //             return_chars(count);
            //             lexical_error(in_char);
            //             return ERROR;
            //         }
            //         count++;
            //     }
            // } else if(again == SECOND){
            //     for(c = getc(file); c != ';'; c = getc(file)){
            //         count_all++;
            //         buffer_char(c);
            //         if(isspace(in_char))
            //             continue;
            //         count++;
            //     }
            // }
            // // go back since we still need to check them
            // return_chars(count_all);
            // if(again == FIRST)
            //     ungetc('|', file); // need it for the second revision
            // clear_buffer();
            // if(count > 0){
            //     printf("CONDITIONALOP\n");
            //     return CONDITIONALOP;
            // } else {
            //     lexical_error(in_char);
            //     return ERROR;
            // }


            printf("CONDITIONALOP \n");
            return CONDITIONALOP;

        }else if(in_char == ':'){
            c = getc(file);
            if (c == '='){
                printf("ASSIGNOP\n");
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
                printf("MINUSOP\n");
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
