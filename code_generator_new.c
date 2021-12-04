//
// Created by adam on 03.12.21.
//

#include "code_generator.h"

/*
 * ----------------------USEFULL FUNCTIONS-----------------------
 */

char* convert_string(char* str_toconvert){
    char* string = str_toconvert;
    string_ptr_t string_res = string_init();

    while(*string != '\0'){
        //iteruji přes vstupní string
        if(*string == 92){
            string_append_character(string_res, '\\');
            string_append_character(string_res, '0');
            string_append_character(string_res, '9');
            string_append_character(string_res, '2');
        }else if(*string == 35){
            string_append_character(string_res, '\\');
            string_append_character(string_res, '0');
            string_append_character(string_res, '3');
            string_append_character(string_res, '5');
        }else if(*string <= 32){
            string_append_character(string_res, '\\');
            string_append_character(string_res, '0');
            string_append_character(string_res, ((*string / 10) + 48));
            string_append_character(string_res, ((*string % 10) + 48));
        }else{
            string_append_character(string_res, *string);
        }

        string++;
    }
    return string_res->string;
}

/*
 * ----------------------BUILD IN FUNCTIONS-----------------------
 */

void codeGen_reads(){
    printf("LABEL reads\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS\n");
    printf("DEFVAR TF@out\n");
    printf("READ TF@out string\n");
    printf("PUSHS TF@out\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void codeGen_readi(){
    printf("LABEL readi\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS\n");
    printf("DEFVAR TF@out\n");
    printf("READ TF@out int\n");
    printf("PUSHS TF@out\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void codeGen_readn(){
    printf("LABEL readn\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS\n");
    printf("DEFVAR TF@out\n");
    printf("READ TF@out float\n");
    printf("PUSHS TF@out\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void codeGen_tointeger(){
    printf("LABEL toiteger\n");
    printf("POPS\n");
    printf("FLOAT2INTS\n");
    printf("RETURN\n");
}

void codeGen_substr(){
    printf("LABEL substr\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS\n");
    printf("DEFVAR TF@ret_str\n");
    printf("DEFVAR TF@err\n");
    printf("MOVE TF@ret_str string@\n");
    printf("MOVE TF@err int@1\n");
    printf("DEFVAR TF@s\n");
    printf("POPS\n");
    printf("DEFVAR TF@i\n");
    printf("POPS TF@i\n");
    printf("DEFVAR TF@n\n");
    printf("DEFVAR TF@char\n");
    printf("MOVE TF@char string@\n");
    printf("DEFVAR TF@str_len\n");
    printf("DEFVAR TF@l_limit\n");
    printf("DEFVAR TF@r_limit\n");
    printf("STRLEN TF@str_len TF@s\n");
    printf("LT TF@l_limit TF@i int@0\n");
    printf("NOT TF@l_limit TF@l_limit\n");
    printf("GT TF@r_limit TF@i TF@str_len\n");
    printf("NOT TF@r_limit TF@r_limit\n");
    printf("AND TF@l_limit TF@l_limit TF@r_limit\n");
    printf("LT TF@r_limit TF@n int@0\n");
    printf("NOT TF@r_limit TF@r_limit\n");
    printf("AND TF@l_limit TF@l_limit TF@r_limit\n");
    printf("JUMPIFNEQ _sub_end TF@l_limit bool@true\n");
    printf("MOVE TF@err int@0\n");
    printf("DEFVAR TF@cnt_of_loaded\n");
    printf("MOVE TF@cnt_of_loaded int@0\n");
    printf("LABEL _sub_while\n");
    printf("LT TF@l_limit TF@i TF@str_len\n");
    printf("LT TF@r_limit TF@cnt_of_loaded TF@n\n");
    printf("AND TF@l_limit TF@l_limit TF@r_limit\n");
    printf("JUMPIFNEQ _sub_end TF@l_limit bool@true\n");
    printf("GETCHAR TF@char TF@s TF@i\n");
    printf("CONCAT TF@ret_str TF@ret_str TF@char\n");
    printf("ADD TF@cnt_of_loaded TF@cnt_of_loaded int@1\n");
    printf("LABEL _sub_end\n");
    printf("PUSHS TF@ret_str\n");
    printf("PUSHS TF@err\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void codeGen_ord(){
    printf("LABEL ord\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS\n");
    printf("DEFVAR TF@ascii\n");
    printf("DEFVAR TF@err\n");
    printf("MOVE TF@ascii string@\n");
    printf("MOVE TF@err int@1\n");
    printf("DEFVAR TF@l_limit\n");
    printf("DEFVAR TF@r_limit\n");
    printf("DEFVAR TF@string\n");
    printf("DEFVAR TF@i\n");
    printf("POPS\n");
    printf("POPS\n");
    printf("DEFVAR TF@str_len\n");
    printf("MOVE TF@str_len int@0\n");
    printf("STRLEN TF@str_len TF@string\n");
    printf("SUB TF@str_len TF@str_len int@1\n");
    printf("LT TF@l_limit TF@i int@0\n");
    printf("NOT TF@l_limit TF@l_limit\n");
    printf("GT TF@r_limit TF@i TF@str_len\n");
    printf("NOT TF@r_limit TF@r_limit\n");
    printf("AND TF@l_limit TF@l_limit TF@r_limit\n");
    printf("JUMPIFNEQ _ord_end TF@l_limit bool@true\n");
    printf("MOVE TF@err int@0\n");
    printf("STRI2INT TF@ascii TF@string TF@i\n");
    printf("LABEL _ord_end\n");
    printf("PUSHS TF@ascii\n");
    printf("PUSHS TF@err\n");
    printf("POPFRAME\n");
    printf("RETURN\n");

}

void codeGen_chr(){
    printf("LABEL chr\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("POPS\n");
    printf("DEFVAR TF@ret_str\n");
    printf("MOVE TF@ret_str string@\n");
    printf("DEFVAR TF@err\n");
    printf("MOVE TF@err int@1\n");
    printf("DEFVAR TF@l_limit\n");
    printf("DEFVAR TF@r_limit\n");
    printf("DEFVAR TF@i\n");
    printf("POPS\n");
    printf("LT TF@l_limit TF@i int@0\n");
    printf("NOT TF@l_limit TF@l_limit\n");
    printf("GT TF@r_limit TF@i int@255\n");
    printf("NOT TF@r_limit TF@r_limit\n");
    printf("AND TF@l_limit TF@l_limit TF@r_limit\n");
    printf("JUMPIFNEQ _chr_end TF@l_limit bool@true\n");
    printf("MOVE TF@err int@0\n");
    printf("INT2CHAR TF@ret_str TF@i\n");
    printf("LABEL _chr_end\n");
    printf("PUSHS TF@ret_str\n");
    printf("PUSHS TF@err\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}


/*
 * ----------------------GENERATOR START-----------------------
 */

static int ifCounter = -1;
static int whileCounter = -1;

/*
 * ----------------------MAIN-----------------------
 */

void codeGen_main_start(){
    printf("LABEL main\nCREATEFRAME\n");
}

void codeGen_main_end(){
    printf("LABEL main$end");
    printf("CLEARS");
}


/*
 * ----------------------VAR-----------------------
 */

void codeGen_push_var(char* name){
    printf("PUSH TF@%s\n", name);
}

void codeGen_push_string(char* value){
    printf("PUSH string@%s\n", convert_string(value));
}

void codeGen_push_int(int value){
    printf("PUSH int@%d\n", value);
}

void codeGen_push_float(double value){
    printf("PUSH float@%a\n", value);
}

void codeGen_new_var(char* name){
    printf("DEFVAR TF@%s\n", name);
}

void codeGen_assign_var(char* name){
    printf("POPS TF@%s", name);
}

/*
 * ----------------------IF-----------------------
 */

void codeGen_if_start(){
    ifCounter++;
    printf("JUMPIFNEQ if$%d$else GF@expr bool@true\n", ifCounter);

}

void codeGen_if_else(){
    printf("JUMP if$%d$end\n", ifCounter);
    printf("LABEL if$%d$else\n", ifCounter);
}

void codeGen_if_end(){
    printf("LABEL if$%d$end\n", ifCounter);
    ifCounter--;
}

/*
 * ----------------------WHILE-----------------------
 */

void codeGen_while_body_start(int number){
    whileCounter++
    printf("LABEL while$%d$start\n", whileCounter);
}

void codeGen_while_start(int number){
    printf("JUMPIFNEQ while$%d$end GF@expr bool@false\n", whileCounter);
}

void codeGen_while_end(int number){
    printf("JUMP while$%d$start\n", whileCounter);
    printf("LABEL while$%d$end\n", whileCounter);
}


/*
 * ----------------------FUNC-----------------------
 */

void codeGen_function_start(char* name){
    printf("LABEL %s\nPUSHFRAME\nCREATEFRAME\n", name);
}

void codeGen_function_end(char* name){
    printf("LABEL %s$end\nPOPFRAME\nRETURN\n", name);
}

void codeGen_function_call(char* name, int parameters){
    printf("PUSH int@%i\n", prameters);
    printf("CALL %s\n");
}

/*
 * ----------------------STACK OPERATION-----------------------
 */

void generate_operation(psa_rules_enum operation){
    switch (operation){
        case NT_PLUS_NT:
            //rule E -> E + E
            printf("ADDS\n");
            break;
        case NT_MINUS_NT:
            //rule E -> E - E
            printf("SUBS\n");
            break;
        case NT_MUL_NT:
            // rule E -> E * E
            printf("MULS\n");
            break;
        case NT_DIV_NT:
            // rule E -> E / E
            printf("DIVS\n");
            break;
        case NT_IDIV_NT:
            // rule E -> E // E
            printf("IDIVS\n");
            break;
        case NT_CONCAT_NT:
            // rule E -> E .. E
            printf("POPS GF@tmp1\n");
            printf("POPS GF@tmp2\n");
            printf("CONCAT GF@tmp3 GF@tmp1 GF@tmp2\n");
            printf("PUSHS GF@tmp3\n");
            break;
        case NT_EQ_NT:
            // rule E -> E == E
            printf("EQS\n");
            break;
        case NT_NEQ_NT:
            // rule E -> E ~= E
            printf("NOT EQS\n");
            break;
        case NT_LEQ_NT:
            // rule E -> E <= E
            printf("GTS\nNOTS\n");
            break;
        case NT_GEQ_NT:
            // rule E -> E >= E
            printf("LTS\nNOTS\n");
            break;
        case NT_LTN_NT:
            // rule E -> E < E
            printf("LTS\n");
            break;
        case NT_GTN_NT:
            // rule E -> E > E
            printf("GTS\n");
            break;
        case NT_HASHTAG:
            // rule E -> #E
            printf("POPS GF@tmp1\n");
            printf("STRLEN GF@tmp4 GF@tmp1\n");
            printf("PUSHS GF@tmp4");
            break;
        default:break;
    }
}