#ifndef TECH_H_
#define TECH_H_
 
#include "../tree/tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <dirent.h>

void StartLatex(FILE* tex);
void EndLatex(FILE* tex);
void WriteAfterMode(FILE* tex, int is_diff_mode, int n);
void PrintNewExpression(Tree* tree, FILE* tex, char* outfile_name, int fig_number);
void PrintExpression(Node* node, FILE* tex, FILE* out);

#endif // #define DIF_H_