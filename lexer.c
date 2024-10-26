#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "lexer.h"

const char *c_keywords[] = {
    "auto","break","char","case","const","continue","default","do","else","enum","extern","float","for",
    "goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void",
    "while","volatile"
};

#define NUM_KEYWORDS (sizeof(c_keywords)/sizeof(c_keywords[0]))

void skipWhiteSpace(FILE* source,int line){
    int c;
    while((c=fgetc(source))!=EOF){
        if(c=='\n') line++;
        if(c!=' ' && c!='\n' && c!='\t'){
            ungetc(c,source);
            break;
        }
    }
}

int isidentifierStart(char c){
    return isalpha(c) || c=='_';
}

int isidentifierChar(char c){
    return isalnum(c) || c=='_';
}

Token* createToken(tokenType type,char* value,int line){
    Token* token=(Token*)malloc(sizeof(Token));
    token->type=type;

    token->value = malloc(strlen(value)+1);

    strcpy(token->value,value);

    token->line = line;

    return token;
}

Token* getNextToken(FILE* source){
    int c;
    static int line=1;

    skipWhiteSpace(source,line);

    c=fgetc(source);

    if(c==EOF){
        return createToken(TOKEN_EOF,"EOF",line);
    }
    
    //For identifier
    if(isidentifierStart(c)){
        char buffer[255];
        int i=0;

        do{
            buffer[i++]=c;
            c=fgetc(source);
        }while(isidentifierChar(c) && i<254);

        buffer[i]='\0';
        if(c!=EOF) ungetc(c,source);
        for(size_t i=0;i<NUM_KEYWORDS; i++){
            if(!strcmp(buffer,c_keywords[i])){
                return createToken(TOKEN_KEYWORD,buffer,line);
            }
        }
        return createToken(TOKEN_IDENTIFIER,buffer,line);
    }

    //for digits constants
    if(isdigit(c)){
        char buffer[255];
        int i=0;

        do{
            buffer[i++]=c;
            c=fgetc(source);
        }while(isdigit(c) && i<254);

        buffer[i]='\0';
        if(c!=EOF) ungetc(c,source);

        return createToken(TOKEN_CONSTANT,buffer,line);
    }
    //for identifying punctuators and operators
    switch(c){
        case '(': return createToken(TOKEN_PUNCTUATOR,"(",line); 
        case ')': return createToken(TOKEN_PUNCTUATOR,")",line); 
        case '{': return createToken(TOKEN_PUNCTUATOR,"{",line); 
        case '}': return createToken(TOKEN_PUNCTUATOR,"}",line); 
        case ';': return createToken(TOKEN_PUNCTUATOR,";",line); 
        case '+': return createToken(TOKEN_OPERATOR,"+",line); 
        case '-': return createToken(TOKEN_OPERATOR,"-",line); 
        case '*': return createToken(TOKEN_OPERATOR,"*",line); 
        case '/': return createToken(TOKEN_OPERATOR,"/",line);
        case '=': return createToken(TOKEN_OPERATOR,"=",line); 

    }
return NULL;
    //for constants
}