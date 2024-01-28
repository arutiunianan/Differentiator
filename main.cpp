#include "dif.h"

int main()
{
    Dif dif = {};
    DifCtor( &dif, "test.txt", "test.txt" );
    TreeFill( &dif );
    //printf("\nALL IS OKAY\n");
}