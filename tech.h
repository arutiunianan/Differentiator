#ifndef TECH_H_
#define TECH_H_

//#include "dif.h"
#include "tree/tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


//#include <Python.h>

void StartLatex( FILE* log );
void EndLatex( FILE* log );
//void PrintNewExpression( Dif* dif, FILE* log, FILE* out );
void PrintNewExpression( Tree* tree, FILE* log, FILE* out );
void PrintExpression( Node* node, FILE* log, FILE* out );

#endif // #define DIF_H_