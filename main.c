#include<stdio.h>
#include<stdlib.h>
#include "lexer.h"
#include "parser.h"

char *Token_names[]={
    "TOKEN_IDENTIFIER",
    "TOKEN_CONSTANT",
    "TOKEN_KEYWORD",
    "TOKEN_PUNCTUATOR",
    "TOKEN_OPERATOR",
    "TOKEN_LITERAL",
    "TOKEN_EOF"
};

int main(){
    FILE* source=fopen("test.c","r");
    //Token* token;

   /* while((token = getNextToken(source))!=NULL){
        if(token->type==TOKEN_EOF){
            free(token->value);
            free(token);
            break;
        }
        printf("%s : %s \n",Token_names[token->type],token->value);
        
        free(token->value);
        free(token);
    }*/
   //advanceToken(source);

    parse_it(source);
    
    fclose(source);
    //free(token);
    return 0;
}