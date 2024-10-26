#include<stdio.h>
#include "token.h"

void skipWhiteSpace(FILE*,int);
Token* getNextToken(FILE*);
Token* createToken(tokenType type, char* value, int line);
