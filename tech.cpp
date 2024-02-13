#include "tech.h"

void StartLatex( FILE* log )
{
    fprintf( log, "\\documentclass{article}\n\n" );
    fprintf( log, "\\usepackage{graphicx}\n");
    fprintf( log, "\\title{Anishe4ka Differentiator}\n");
    fprintf( log, "\\author{ani}\n");
    fprintf( log, "\\date{Febrary 2024} \n");
    fprintf( log, "\\begin{document}\n");
    fprintf( log, "\\maketitle\n");
}

void EndLatex( FILE* log )
{
    /*Py_Initialize();
    FILE* fp = fopen("fig_maker", "rb");
    if(fp)
        PyRun_SimpleFile(fp, "fig_maker");
    Py_Finalize();*/

    fprintf( log, "\\end{document}");
}

//void PrintNewExpression( Dif* dif, FILE* log, FILE* out )
void PrintNewExpression( Tree* tree, FILE* log, FILE* out )
{
    fprintf( log, "$");
    
    //PrintExpression( dif->tree->root, log, out );
    PrintExpression( tree->root, log, out );

    fprintf( log, "$\\newline\n");
}

void PrintExpression( Node* node, FILE* log, FILE* out )
{
    if( node->value->type == NUM_TYPE )
        if( node->value->arg == (int) node->value->arg )
        {
            fprintf( log, "%d", (int) node->value->arg);
            fprintf( out, "%d", (int) node->value->arg);
        }
        else
        {
            fprintf( log, "%lf",node->value->arg);
            fprintf( out, "%lf",node->value->arg);
        }
    else if( node->value->type == VAR_TYPE )
    {
        fprintf( log, "%c", (char) node->value->arg);
        fprintf( out, "%c", (char) node->value->arg);
    }
    else if( node->value->type == OPER_TYPE && (char) node->value->arg == 'p' )
    {
        fprintf( log, "pi");
        fprintf( out, "pi");
    }
    else if( node->value->type == OPER_TYPE && (char) node->value->arg == 'e' )
    {
        fprintf( log, "e");
        fprintf( out, "exp(1)");
    }
    else if( node->value->type == OPER_TYPE )
        switch ( (char) node->value->arg )
		{
			#define OPER_DEF( value, designation, differentiate_code, tech_code )  \
            case designation:  \
                tech_code;  \
                break; \
				
			#include "defs.h"
			#undef OPER_DEF
		}
}
