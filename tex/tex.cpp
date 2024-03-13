#include "tex.h"

void StartLatex(FILE* tex)
{
    assert(tex != NULL);

    fprintf(tex, "\\documentclass{article}\n\n");
    fprintf(tex, "\\usepackage{graphicx}\n");
    fprintf(tex, "\\title{Anishe4ka Differentiator}\n");
    fprintf(tex, "\\author{ani}\n");
    fprintf(tex, "\\date{Febrary 2024} \n");
    fprintf(tex, "\\begin{document}\n");
    fprintf(tex, "\\maketitle\n");
}

void EndLatex(FILE* tex)
{
    assert(tex != NULL);

    fprintf(tex, "\\end{document}");
}

void WriteAfterMode(FILE* tex, int is_diff_mode, int n)
{
    assert(tex != NULL);

    if(is_diff_mode)
    {
        fprintf(tex, "After %d-times differentiation:\\newline\n", n);
    }
    else
    {
        fprintf(tex, "After decomposing into a Maclaurin series of %d-degree:\\newline\n", n);
    }
}

void PrintNewExpression(Tree* tree, FILE* tex, char* outfile_name, int fig_number)
{
    assert(tree != NULL);
    assert(tex != NULL);
    assert(outfile_name != NULL);
    TreeDump(tree, tree->log);

    FILE* out = fopen(outfile_name,"wb");
    assert(out != NULL);
    if(fig_number % 3 == 0)
    {
        fprintf(tex, "\\newpage\n");
        fprintf(tex, "\\section{Expression:}\n");
    }
    else if(fig_number % 3 == 2)
    {
        fprintf(tex, "After optimization:\\newline\n");
    }
    fprintf(tex, "$");
    PrintExpression(tree->root, tex, out);
    fprintf(tex, "$\\newline\\newline\n");
    fclose(out);

    if(fig_number % 3 == 2)
    {
        char py_call[82] = "";
        snprintf(py_call, 82, "python3.8 figs/fig_maker.py differentiator/in.txt differentiator/optim_out.txt %d", fig_number / 3);
        system(py_call);
        fprintf(tex, "\\begin{figure} [!ht]\n");
        fprintf(tex, "\\begin{flushleft}\n");
        fprintf(tex, "\\includegraphics[scale = 0.700000]{figs/fig%d.png}\n", fig_number / 3);
        fprintf(tex, "\\end{flushleft}\n");
        fprintf(tex, "\\end{figure}\n");
    }
    TreeDump(tree, tree->log);
}

void PrintExpression(Node* node, FILE* tex, FILE* out)
{
    assert(node != NULL);
    assert(tex != NULL);
    assert(out != NULL);

    if(node->value->type == NUM_TYPE)
    {
        if(node->value->arg == (int) node->value->arg)
        {
            fprintf(tex, "%d", (int) node->value->arg);
            fprintf(out, "%d", (int) node->value->arg);
        }
        else
        {
            fprintf(tex, "%lf", node->value->arg);
            fprintf(out, "%lf", node->value->arg);
        }
    }
    else if(node->value->type == VAR_TYPE)
    {
        fprintf(tex, "%c", (char) node->value->arg);
        fprintf(out, "%c", (char) node->value->arg);
    }
    else if(node->value->type == OPER_TYPE && (char) node->value->arg == 'p')
    {
        fprintf(tex, "pi");
        fprintf(out, "pi");
    }
    else if(node->value->type == OPER_TYPE && (char) node->value->arg == 'e')
    {
        fprintf(tex, "e");
        fprintf(out, "exp(1)");
    }
    else if(node->value->type == OPER_TYPE)
    {
        switch ((char) node->value->arg)
        {
            #define OPER_DEF(value, designation, differentiate_code, tech_code)  \
            case designation:                                                     \
                tech_code;                                                         \
                break;                                                              \
                
            #include "../differentiator/defs.h"
            #undef OPER_DEF
        }
    }
}
