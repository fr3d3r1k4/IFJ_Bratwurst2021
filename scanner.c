/**
 * Project: Compiler for IFJ21 language
 * 
 * Brief:   Lexical Analysis for IFJ21 compiler
 * 
 * Author:  Adam Kankovsky   <xkanko00@stud.fit.vutbr.cz>
 * Author:  Stepan Bakaj     <xbakaj00@stud.fit.vutbr.cz>
 * Author:  Radek Serejch    <xserej00@stud.fit.vutbr.cz>
 * Author:  David Chocholaty <xchoch09@stud.fit.vutbr.cz>
 * 
 * Date:    23-10-2021
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "scanner.h"
#include "string.h"
#include "error.h"

#define ASCII_PRINTABLE 32
#define ASCII_NUMS_START 48


void set_id_keyword (token_t* token, char* str){
    if(strcmp(str,"do")==0){
        token->attribute.keyword = K_DO;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"else")==0){
        token->attribute.keyword = K_ELSE;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"end")==0){
        token->attribute.keyword = K_END;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"function")==0){
        token->attribute.keyword = K_FUNCTION;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"global")==0){
        token->attribute.keyword = K_GLOBAL;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"if")==0){
        token->attribute.keyword = K_IF;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"integer")==0){
        token->attribute.keyword = K_INTEGER;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"local")==0){
        token->attribute.keyword = K_LOCAL;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"nil")==0){
        token->attribute.keyword = K_NIL;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"number")==0){
        token->attribute.keyword = K_NUMBER;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"require")==0){
        token->attribute.keyword = K_REQUIRE;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"return")==0){
        token->attribute.keyword = K_RETURN;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"string")==0){
        token->attribute.keyword = K_STRING;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"then")==0){
        token->attribute.keyword = K_THEN;
        token->type=T_KEYWORD;
    }else if(strcmp(str,"while")==0){
        token->attribute.keyword = K_WHILE;
        token->type=T_KEYWORD;
    }else{
        token->type=T_IDENTIFIER;
        token->attribute.string=str;
    }
}

token_t* create_token ()
{
    return (token_t*) malloc(sizeof(token_t));
}

void delete_token (token_t* token)
{
    // TODO
}

token_t* get_next_token ()
{
    char symbol; //readed character from stdin
    token_t* token;
    string_ptr_t str;
    state_t state = S_INIT;        

    token = create_token();

    if (!token)
    {
        err = E_INTERNAL;
        return NULL;
    }    

    if (!string_init(str))
    {
        err = E_INTERNAL;
        delete_token(token);
        
        return NULL;
    }            


    while (read(1, &symbol, 1))
    {              
        switch (state)
        {            
            //**************** INIT STATE ****************//            
            case (S_INIT):
                if (symbol == '#')
                {
                    token->type = T_CHAR_CNT;
                }
                else if (symbol == '*')
                {
                    token->type = T_MUL;
                }
                else if (symbol == '/')
                {
                    state = S_DIV;
                }
                else if (symbol == '+')
                {
                    token->type = T_PLUS;
                }
                else if (symbol == '-')
                {
                    state = S_MINUS;
                }
                else if (symbol == '.')
                {
                    state = S_DOT;
                }
                else if (symbol == '<')
                {
                    state = S_LESS_THAN;
                }
                else if (symbol == '>')
                {
                    state = S_GTR_THAN;
                }
                else if (symbol == '~')
                {
                    state = S_TILDE;
                }
                else if (symbol == '=')
                {
                    state = S_ASSIGN;
                }
                else if (symbol == ':')
                {
                    token->type = T_COLON;
                }
                else if (symbol == '(')
                {
                    token->type = T_LEFT_BRACKET;
                }
                else if (symbol == ')')
                {
                    token->type = T_RIGHT_BRACKET;
                }
                else if (symbol == ',')
                {
                    token->type = T_COMMA;
                }
                else if (isdigit(symbol))
                {
                    state = S_INT;
                    string_append_character(str, symbol);
                }
                else if (isalpha(symbol) || symbol == '_')
                {
                    state = S_IDENTIFIER_KEYWORD;
                    string_append_character(str, symbol);
                    
                }
                else if (symbol == '"')
                {
                    state = S_STRING_CONTENT;
                }                
                else if (symbol != '\n' && symbol != '\t' && symbol != ' ')
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }

                break;

            //***************** Q STATES *****************//            
            case (S_ONE_LINE_COMMENT):
                if (symbol == '[')
                {
                    state = S_LEFT_SQUARE_BRACKET;
                }
                else
                {
                    state = S_ONE_LINE_COMMENT_CONTENT;
                }
                
                break;

            case (S_ONE_LINE_COMMENT_CONTENT):                                   
                if (symbol == '\n')
                {
                    state = S_INIT;
                }                

                break; 

            case (S_LEFT_SQUARE_BRACKET): 
                if (symbol == '[')
                {
                    state = S_BLOCK_COMMENT_CONTENT;
                }   
                else
                {
                    state = S_ONE_LINE_COMMENT_CONTENT;
                }

                break;

            case (S_BLOCK_COMMENT_CONTENT):
                if (symbol == ']')
                {
                    state = S_RIGHT_SQUARE_BRACKET;
                }

                break;

            case (S_RIGHT_SQUARE_BRACKET):
                if (symbol == ']')
                {
                    state = S_INIT;
                }
                else
                {
                    state = S_BLOCK_COMMENT_CONTENT;
                }

                break;

            case (S_DOT):
                if (symbol == '.')
                {
                    token->type = T_CONCAT;
                }
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }

                break;

            case (S_TILDE):
                if (symbol == '=')
                {
                    token->type = T_NOT_EQ;
                }
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }  

                break;

            case (S_DECIMAL_POINT):     
                if (isdigit(symbol))
                {
                    state = S_DECIMAL;
                    string_append_character(str, symbol);
                }
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }

                break;

            case (S_EXP):
                if (symbol == '+' || symbol == '-')
                {
                    state = S_EXP_PLUS_MINUS;
                    string_append_character(str, symbol);
                }
                else if(isdigit(symbol))
                {
                    state = S_DECIMAL_W_EXP;
                    string_append_character(str, symbol);
                }
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }

                break;

            case (S_EXP_PLUS_MINUS):
                if (isdigit(symbol))
                {
                    state = S_DECIMAL_W_EXP;
                    string_append_character(str, symbol);
                }
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }

                break;

            case (S_STRING_CONTENT):            
                if (symbol == '"')
                {                    
                    token->type = T_STRING;
                    token->attribute.string = get_char_arr(str);
                }
                else if (symbol == '\\')
                {
                    state = S_ESC_SEQ_BACKSLASH;
                }
                else if((int)symbol < ASCII_PRINTABLE)
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                } 

                break;

            case (S_ESC_SEQ_BACKSLASH):
                if (symbol == '0')
                {
                    state = S_ESC_SEQ_ZERO;
                }
                else if (symbol == '1')
                {
                    state = S_ESC_SEQ_ONE;
                }
                else if (symbol == '2')
                {
                    state = S_ESC_SEQ_TWO;
                }
                else if (symbol == '"' || symbol == 'n' || 
                         symbol == 't' || symbol == '\\')
                {
                    state = S_STRING_CONTENT;
                }                
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }

                break;

            case (S_ESC_SEQ_ZERO):
                if (symbol == '0')
                {
                    state = S_ESC_SEQ_DOUBLE_ZERO;
                }
                else if (isdigit(symbol))
                {
                    state = S_ESC_SEQ_X_X;
                }
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }

                break;

            case (S_ESC_SEQ_DOUBLE_ZERO):
                if (isdigit(symbol) && symbol != '0')
                {
                    state = S_STRING_CONTENT;
                }
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }

                break;

            case (S_ESC_SEQ_ONE):
                if (isdigit(symbol))
                {
                    state = S_ESC_SEQ_X_X;
                }
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }

                break;

            case (S_ESC_SEQ_X_X):
                if (isdigit(symbol))
                {
                    state = S_STRING_CONTENT;
                }
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }

                break;

            case (S_ESC_SEQ_TWO):
                if (symbol == '5')
                {
                    state = S_ESC_SEQ_TWO_FIVE;
                }
                else if (isdigit(symbol) && 
                         ((int)symbol - ASCII_NUMS_START) < 5)
                {
                    state = S_ESC_SEQ_X_X;
                }
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }

                break;

            case (S_ESC_SEQ_TWO_FIVE):
                if (isdigit(symbol) && 
                    ((int)symbol - ASCII_NUMS_START) <= 5)
                {
                    state = S_STRING_CONTENT;
                }
                else
                {
                    err = E_LEX;
                    delete_token(token);
                    string_free(str);

                    return NULL;
                }
                
                break;                
            
            //***************** F STATES *****************//
            case (S_DIV):
                if (symbol == '/')
                {
                    token->type = T_INT_DIV;
                }
                else
                {
                    if (ungetc(symbol, stdin) == EOF)
                    {
                        err = E_INTERNAL;
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }                    

                    token->type = T_DIV;

                    return token;
                }                
                
                break;       

            case (S_MINUS):
                if (symbol == '-')
                {
                    state = S_ONE_LINE_COMMENT;
                }
                else
                {
                    if (ungetc(symbol, stdin) == EOF)
                    {
                        err = E_INTERNAL;
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }

                    token->type = T_MINUS;

                    return token;
                }
                
                break;                                             

            case (S_LESS_THAN):
                if (symbol == '=')
                {
                    token->type = T_LESS_EQ;
                }
                else
                {
                    if (ungetc(symbol, stdin) == EOF)
                    {
                        err = E_INTERNAL;
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }

                    token->type = T_LESS_THAN;
                    
                    return token;
                }

                break;        

            case (S_GTR_THAN):
                if (symbol == '=')
                {
                    token->type = T_GTR_EQ;
                }
                else
                {
                    if (ungetc(symbol, stdin) == EOF)
                    {
                        err = E_INTERNAL;
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }

                    token->type = T_GTR_THAN;

                    return token;
                }

                break;                

            case (S_ASSIGN):
                if (symbol == '=')
                {
                    token->type = T_EQ;
                }
                else
                {
                    if (ungetc(symbol, stdin) == EOF)
                    {
                        err = E_INTERNAL;
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }

                    token->type = T_ASSIGN;

                    return token;
                }

                break;                               
            
            case (S_INT):
                if (symbol == 'e' || symbol == 'E')
                {                    
                    state = S_EXP;
                    string_append_character(str, symbol);
                }
                else if (symbol == ".")
                {
                    state = S_DECIMAL_POINT;
                    string_append_character(str, symbol);
                }
                else if (isdigit(symbol))
                {
                    string_append_character(str, symbol);                    
                }                
                else
                {
                    if (ungetc(symbol, stdin) == EOF)
                    {
                        err = E_INTERNAL;
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }

                    token->type = T_INT;                                        
                    token->attribute.integer = string_to_int(str);

                    if (err != E_NO_ERR)
                    {
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }
                    
                    
                    return token;
                }                                
                
                break;
            case (S_DECIMAL):                
                if (symbol == 'e' || symbol == 'E')
                {
                    state = S_EXP;
                    string_append_character(str, symbol);
                }
                else if (isdigit(symbol))
                {
                    string_append_character(str, symbol);
                }
                else
                {
                    if (ungetc(symbol, stdin) == EOF)
                    {
                        err = E_INTERNAL;
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }

                    token->type = T_DECIMAL;                    
                    token->attribute.decimal = string_to_dec(str);

                    if (err != E_NO_ERR)
                    {
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }
                    

                    return token;
                }
                                
                break;

            case (S_IDENTIFIER_KEYWORD):
                if (isalpha(symbol) || isdigit(symbol))
                {
                    string_append_character(str, symbol);
                }
                else
                {
                    if (ungetc(symbol, stdin) == EOF)
                    {
                        err = E_INTERNAL;
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }                                     
                    
                    char* id_keyword = get_char_arr(str);

                    if (err == E_NO_ERR)
                    {
                        set_id_keyword(token, id_keyword);
                    }
                    else
                    {
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }                                         

                    return token;
                }
                
                break;

            case (S_DECIMAL_W_EXP):
                if (isdigit(symbol))
                {
                    string_append_character(str, symbol);
                }
                else
                {
                    if (ungetc(symbol, stdin) == EOF)
                    {
                        err = E_INTERNAL;
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }

                    token->type = T_DECIMAL_W_EXP;
                    token->attribute.decimal = string_to_dec(str);

                    if (err != E_NO_ERR)
                    {
                        delete_token(token);
                        string_free(str);

                        return NULL;
                    }

                    return token;
                }
                
                break;                               
        }
    }

    delete_token(token);
    string_free(str);

    return NULL;
}