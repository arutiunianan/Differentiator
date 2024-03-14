#ifndef MAC_H_
#define MAC_H_
 
#include "differentiator.h"

Tree* MaclaurinSeries(Dif_file* dif_file, char var, int n);
Tree* CopyTreeForMaclaurin(Tree* tree, char var, int isMaclaurin);
Node* CopyNodesForMaclaurin(Node* node, char var, int isMaclaurin );

#endif // #define MAC_H_