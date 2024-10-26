#include<stdlib.h>

void advanceToken(FILE*);
void parse_it(FILE*);
typedef enum{
    AST_ASSIGNMENT,
    AST_BINARYEXP,
    AST_IDENTIFIER,
    AST_CONSTANT
}ASTNodeType;

typedef struct ASTNode{
    ASTNodeType type;
    struct ASTNode* left;
    struct ASTNode* right;
    char* value; // for id names and values
}ASTNode;