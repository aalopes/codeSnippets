// Passing VLAs to function

// Note that the function argument needs to be different for VLAs
// They do have a different type, and if not doing so, the compiler
// will complain.
// Normal arrays with compile-time fixed dimensions will work as
// well.

// Alexandre Lopes

#include <stdio.h>
#include <stdlib.h>

void arrayPrint (int dim1, int dim2, double array[dim1][dim2])
{
    int i, j;
    for (i = 0; i < dim1; i++)
    {
        for (j = 0; j < dim2; j++)
        {
            printf("%f \n", array[i][j]);
        }
    }
}

int main()
{
    int dim1  = 5;
    int dim2  = 6;
    int i, j;

    // Stack allocaterd VLAs
    double array[dim1][dim2];

    for (i = 0; i < dim1; i++)
    {
        for (j = 0; j < dim2; j++)
        {
            array[i][j] = i+j;
        }
    }

    // 'Normal' array of compile-time fixed dimension
    double a[5][5];
    arrayPrint(dim1, dim2, array);
    printf("\n");
    arrayPrint(dim1, dim2, a);

    return 0;
}
