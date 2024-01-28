#ifndef DIF_H_
#define DIF_H_

#include "tree/tree.h"
#include "defs.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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


Node* GetE( char** str );
Node* GetN( char** str );
Node* GetW( char** str );
Node* GetT( char** str );
Node* GetP( char** str );
Node* GetF( char** str );
Node* GetG( char** str );

#endif // #define DIF_H_