#ifndef DIF_H_
#define DIF_H_

#include "tech.h"
/*#include "tree/tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>*/
//#define LEFT node->left
//#define RIGHT node->right

#define _ADD(left_node, right_node) CreateNodeWithType( OPER_TYPE, ADD, left_node, right_node)
#define _SUB(left_node, right_node) CreateNodeWithType( OPER_TYPE, SUB, left_node, right_node)
#define _MUL(left_node, right_node) CreateNodeWithType( OPER_TYPE, MUL, left_node, right_node)
#define _DIV(left_node, right_node) CreateNodeWithType( OPER_TYPE, DIV, left_node, right_node)
#define _POW(left_node, right_node) CreateNodeWithType( OPER_TYPE, POW, left_node, right_node)

typedef struct Dif
{
    Tree* tree;
    FILE* log;

    FILE* input;
    int file_size;
    char* buffer;

    FILE* output;
    int errors;
}Dif;

void DifCtor( Dif* dif, const char* input, const char* output );
int TreeFill( Dif* dif );
Node* CreateNodeWithType( int type, double arg );
Node* CreateNodeWithType( int type, double arg, Node* val );
Node* CreateNodeWithType( int type, double arg, Node* val1, Node* val2 );
Node* DifferentiateNode( Node* node, char var);
//Node* Optimization( Node* node );
void DifferentiateNTimes( Dif* dif, FILE* log, char var, int n );
void Optimization( Node* node );

Tree* MaclaurinSeriesBeforeN( Dif* dif, char var, int n );
Tree* CopyTreeForMaclaurin( Tree* tree, char var, int isMaclaurin );
Node* CopyNodesForMaclaurin( Node* node, char var, int isMaclaurin  );


Node* GetE( char** str );
Node* GetN( char** str );
Node* GetW( char** str );
Node* GetT( char** str );
Node* GetP( char** str );
Node* GetF( char** str );
Node* GetG( char** str );

#endif // #define DIF_H_