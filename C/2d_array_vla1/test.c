// Example of the impossibility of returning a VLA array, since these are
// automatic objects and deallocated when they out of scope (in this case,
// the malloc'ed object is not automatically deallocated, but the pointer
// which points to that memory region is.)

// Reference <http://stackoverflow.com/questions/30438159/return-vla-and-usage>

// This example WILL most likely SEGFAULT

// Alexandre Lopes

#include <stdio.h>
#include <stdlib.h>


double** arrayAlloc2D (int dim1, int dim2)
{

    /* allocate VLA on the heap */
    double (*array)[dim1];
    array = malloc(sizeof( double ) *dim1 * dim2);

    return (double**) array;
}

int main()
{
    int dim1  = 50;
    int dim2  = 100;
    int i, j;
    
    double** array = arrayAlloc2D(dim1, dim2);

    for (i = 0; i < dim1; i++)
    {
        for (j = 0; j < dim2; j++)
        {
            array[i][j] = i*j;
        }
    }
    
    for (i = 0; i < dim1; i++)
    {
        for (j = 0; j < dim2; j++)
        {
            printf("%f \n", array[i][j]);
        }
    }

    // a free should go in here, but there's no point since this will
    // segfault before.

    return 0;
}
