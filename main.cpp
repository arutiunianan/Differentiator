//#include "tech.h"
#include "dif.h"

int main()
{
    FILE* log = fopen( "tex.tex","wb" );
    FILE* out1 = fopen( "out1.txt","wb" );
    FILE* out2 = fopen( "out2.txt","wb" );
    FILE* out3 = fopen( "out4.txt","wb" );
    //FILE* out4 = fopen( "out3.txt","wb" );

    Dif dif = {};
    StartLatex( log );
    DifCtor( &dif, "test.txt", "test.txt" );
    TreeFill( &dif );
    PrintNewExpression(dif.tree,log,out1);

    //TreeDump( dif.tree, dif.tree->log );
    DifferentiateNTimes( &dif, log, 'u', 0 );
    Optimization( dif.tree->root );
    PrintNewExpression( dif.tree ,log,out2);

    /*Tree* new_tree = ( Tree* )calloc( 1, sizeof( Tree ) );
    new_tree->errors = dif.tree->errors;
    new_tree->log = dif.tree->log;
    new_tree->size = dif.tree->size;
    new_tree->root = DifferentiateNode( dif.tree->root, 'u');*/
    //Optimization( dif.tree->root );
    //PrintNewExpression( dif.tree ,log,out3);

    
    dif.tree = MaclaurinSeriesBeforeN( &dif, 'u', 3 );
    PrintNewExpression( dif.tree ,log,out3);

    

    Optimization( dif.tree->root );
    PrintNewExpression( dif.tree ,log,out3);


TreeDump( dif.tree, dif.tree->log );
    

    EndLatex( log );
}