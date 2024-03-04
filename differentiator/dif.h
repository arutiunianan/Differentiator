#ifndef DIF_H_
#define DIF_H_

#include "../tex/tex.h"

#define LEFT node->left
#define RIGHT node->right

#define _ADD(left_node, right_node) CreateNodeWithType(OPER_TYPE, ADD, left_node, right_node)
#define _SUB(left_node, right_node) CreateNodeWithType(OPER_TYPE, SUB, left_node, right_node)
#define _MUL(left_node, right_node) CreateNodeWithType(OPER_TYPE, MUL, left_node, right_node)
#define _DIV(left_node, right_node) CreateNodeWithType(OPER_TYPE, DIV, left_node, right_node)
#define _POW(left_node, right_node) CreateNodeWithType(OPER_TYPE, POW, left_node, right_node)

typedef struct Dif_file
{
    Tree* tree;
    FILE* tex;

    FILE* input;
}Dif_file;

void DifCtor(Dif_file* dif_file, const char* input);
int TreeFill(Dif_file* dif_file);
void DifDtor(Dif_file* dif_file);

Node* CreateNodeWithType(int type, double arg);
Node* CreateNodeWithType(int type, double arg, Node* val);
Node* CreateNodeWithType(int type, double arg, Node* val1, Node* val2);
Node* DifferentiateNode(Node* node, char var);
void DifferentiateNTimes(Dif_file* dif_file, char var, int n);
void Optimization(Node* node);

Tree* MaclaurinSeries(Dif_file* dif_file, char var, int n);
Tree* CopyTreeForMaclaurin(Tree* tree, char var, int isMaclaurin);
Node* CopyNodesForMaclaurin(Node* node, char var, int isMaclaurin );

Node* GetE(char** str);
Node* GetN(char** str);
Node* GetW(char** str);
Node* GetT(char** str);
Node* GetP(char** str);
Node* GetF(char** str);
Node* GetG(char** str);

#endif // #define DIF_H_