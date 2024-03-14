#include "optimization.h"
 
int DoDifAndWrite(Dif_file* dif_file, char* mode, int* fig_number)
{
    int n = 0;
    TreeFill(dif_file);
    
    if(!strcmp(mode, "dif"))
    {
        printf("Degree of differentiation: ");
        scanf("%d", &n);
        PrintNewExpression(dif_file->tree, dif_file->tex, "differentiator/in.txt", *fig_number);
        (*fig_number)++;
        DifferentiateNTimes(dif_file, 'x', n);
        WriteAfterMode(dif_file->tex, 1, n);
    }
    else if(!strcmp(mode, "mac"))
    {
        printf("Degree of the Maclaurin series: ");
        scanf("%d", &n);
        PrintNewExpression(dif_file->tree, dif_file->tex, "differentiator/in.txt", *fig_number);
        (*fig_number)++;
        dif_file->tree = MaclaurinSeries(dif_file, 'x', n);
        WriteAfterMode(dif_file->tex, 0, n);
    }
    else
    {
        return 1;
    }
    PrintNewExpression(dif_file->tree, dif_file->tex, "differentiator/out.txt", *fig_number);
    (*fig_number)++;

    Optimization(dif_file->tree->root);
    PrintNewExpression(dif_file->tree, dif_file->tex, "differentiator/optim_out.txt", *fig_number);
    (*fig_number)++;
    return 0;
}

int main(int argc, const char* argv[])
{
    Dif_file dif_file = {};

    if(argc == 1)
    {
        DifCtor(&dif_file, "test.txt");
    }
    else if(argc == 2)
    {
        DifCtor(&dif_file, argv[1]);
    }
    else
    {
        printf("Invalid number of args to program!\n");
        return 1;
    }

    int fig_number = 0;
    char* mode = (char*)calloc(4, sizeof(char));
    do
    {
        printf("\nChoose the mode\n"
                "1. Differentiate N times\n"
                "2. Maclaurin series\n"
                "3. Exit\n"
                "(print dif/mac/exit)\n");
        scanf("%s", mode);
        
        if(DoDifAndWrite(&dif_file, mode, &fig_number) && strcmp(mode, "exit"))
        {
            printf("Incorrect input. Try again\n");
        }
    } while(strcmp(mode, "exit"));
    
    DifDtor(&dif_file);
    return 0;
}