#include "maclaurin.h"
 
double Factorial(int n)
{
    int factorial = 1;
    for(int i = 1; i <= n; i++)
    {
        factorial = factorial * i;
    }
    return (double) factorial;
}

Tree* JoinTreesWithSumAndCoef(Tree* left_tree, Tree* right_tree, char var, int n)
{
    TreeDump(left_tree, left_tree->log);
    TreeDump(right_tree, right_tree->log);
    right_tree->root = _MUL(right_tree->root, _DIV(CreateNodeWithType(NUM_TYPE, 1), CreateNodeWithType(NUM_TYPE, Factorial(n))));
    right_tree->root = _MUL(right_tree->root, _POW(CreateNodeWithType(VAR_TYPE, var), CreateNodeWithType(NUM_TYPE, n)));
    left_tree->root = _ADD(left_tree->root, right_tree->root);
    left_tree->size = left_tree->size + right_tree->size;
    TreeDump(left_tree, left_tree->log);
    TreeDump(right_tree, right_tree->log);
    return left_tree;
}

Tree* MaclaurinSeries(Dif_file* dif_file, char var, int n)
{
    TreeDump(dif_file->tree, dif_file->tree->log);
    if(n > 0)
    {
        Tree* treeBeforeN = MaclaurinSeries(dif_file, var, n - 1);
        dif_file->tree->root = DifferentiateNode(dif_file->tree->root, var);
        return JoinTreesWithSumAndCoef(treeBeforeN, CopyTreeForMaclaurin(dif_file->tree, var, 1), var, n);
    }
    else if(n == 0)
    {
        return CopyTreeForMaclaurin(dif_file->tree, var, 1);
    }
    TreeDump(dif_file->tree, dif_file->tree->log);
}

Tree* CopyTreeForMaclaurin(Tree* tree, char var, int isMaclaurin)
{
    Tree* new_tree = (Tree*)calloc(1, sizeof(Tree));
    new_tree->errors = tree->errors;
    new_tree->log = tree->log;
    new_tree->size = tree->size;
    new_tree->root = CopyNodesForMaclaurin(tree->root, var, isMaclaurin);
    TreeDump(tree, tree->log);
    return new_tree;
}

Node* CopyNodesForMaclaurin(Node* node, char var, int isMaclaurin)
{
    Node* new_node = CopyNode(node);
    if(new_node->value->type == VAR_TYPE && (char) new_node->value->arg == var && isMaclaurin)
    {
        new_node->value->type = NUM_TYPE;
        new_node->value->arg = 0;
    }

    if(LEFT)
    {
        new_node->left = CopyNodesForMaclaurin(LEFT, var, isMaclaurin);
    }
    if(RIGHT)
    {
        new_node->right = CopyNodesForMaclaurin(RIGHT, var, isMaclaurin);
    }
    return new_node;
}