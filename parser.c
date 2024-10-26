#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"lexer.h"
#include "parser.h"

Token* current_token;

void advanceToken(FILE* source){
    if (current_token) {
        free(current_token->value);
        free(current_token);
    }
    current_token=getNextToken(source);
}

ASTNode* createidnode(const char* name){
    ASTNode* node = malloc(sizeof(ASTNode));
    node ->type = AST_IDENTIFIER;
    node -> value = strdup(name);
    node -> left = NULL;
    node ->right =NULL;
    return node;
}

ASTNode* createConstantNode(const char* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_CONSTANT;
    node->value = strdup(value);
    node->left = node->right = NULL;
    return node;
}

ASTNode* createBinaryExptNode(char *op,ASTNode* left, ASTNode* right){
    ASTNode* node =  malloc(sizeof(ASTNode));
    node -> type = AST_BINARYEXP;
    node -> value = strdup(op);
    node ->left = left;
    node -> right = right;
    return node;
}

ASTNode* parsePrimaryExp(FILE* source){
    if(current_token->type== TOKEN_IDENTIFIER){
        ASTNode* node = createidnode(current_token->value);
        advanceToken(source);
        return node;
    }else{
        ASTNode* node = createConstantNode(current_token->value);
        advanceToken(source);
        return node;
    }
}
ASTNode* parseBinaryExp(FILE* source){
    ASTNode* left = parsePrimaryExp(source);
    while((current_token->type == TOKEN_OPERATOR && strcmp(current_token->value,"+")==0 )|| strcmp(current_token->value,"-")==0){
        char op[2]={ current_token->value[0],'\0'};
        advanceToken(source);
        ASTNode* right =parsePrimaryExp(source);
        left=createBinaryExptNode(op,left,right);
    }
    return left;
}
ASTNode* parseAssignment(FILE* source){
    if(current_token->type==TOKEN_IDENTIFIER){
        ASTNode* id= createidnode(current_token->value);
        advanceToken(source);

        if(current_token->type==TOKEN_OPERATOR && strcmp(current_token->value,"=")==0){
            advanceToken(source);
            ASTNode* expr = parseBinaryExp(source);
            ASTNode* assignment = malloc(sizeof(ASTNode));
            assignment->type = AST_ASSIGNMENT;
            assignment->left = id;
            assignment->right = expr;
            assignment->value = strdup("=");
            return assignment;
        }
    }
    return NULL;
}

ASTNode* parsestmt(FILE* source){
    if (current_token->type == TOKEN_IDENTIFIER) {
        return parseAssignment(source);
    }

    return NULL;
}
void printAST(ASTNode* node) {
    if (node == NULL) {
        printf("NULL\n");
        return;
    }

    switch (node->type) {
        case AST_ASSIGNMENT:
            printf("Assignment: %s = ", node->left->value); // Print the identifier
            printAST(node->right); // Print the expression
            break;
        case AST_BINARYEXP:
            printf("Binary Expression: ");
            printAST(node->left); // Print the left operand
            printf(" Operator: %s ", node->value); // Print the operator
            printAST(node->right); // Print the right operand
            break;
        case AST_IDENTIFIER:
            printf("Identifier: %s\n", node->value);
            break;
        case AST_CONSTANT:
            printf("Constant: %s\n", node->value);
            break;
        default:
            printf("Unknown AST Node Type\n");
    }
}

void parse_it(FILE* source){
    advanceToken(source);
    //if(current_token==NULL)
        //printf("%s",current_token->value);
    while(current_token!=NULL && current_token->type!=TOKEN_EOF){
        ASTNode* stmt = parsestmt(source);
        if(stmt){
            printf("Parsed\n");
            printAST(stmt);
        }
        else{
            printf("NOT Parsed");
        }
                    advanceToken(source);

    }
}