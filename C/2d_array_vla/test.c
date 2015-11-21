// 'Heap allocated VLA' (variable length-array) - actually only pointer
// with function for performing the allocation.
// This is a C99 standard!

// Reference <http://stackoverflow.com/questions/30438159/return-vla-and-usage>

// note that returning the pointer will not work, since this is a VLA!
// they are automatic objects and are deallocated if they go out of scope 
// hence the need to use the input parameter

// Alexandre Lopes

#include <stdio.h>
#include <stdlib.h>

int arrayAlloc2D (int dim1, int dim2, double(**array)[dim1][dim2])
{

    /* allocate VLA on the heap */
    (*array) = malloc(sizeof( **array ));
    if ((*array) == NULL )
    {
        return -1;
    }

    return 0;
}

int main()
{
    int dim1  = 5;
    int dim2  = 5;
    int i, j;
    
    double (*array)[dim1][dim2] = NULL; 
    int ret = arrayAlloc2D(dim1, dim2, &array); // return value should be checked
    if (ret == -1)
    {
       return -1;
    }
    
    for (i = 0; i < dim1; i++)
    {
        for (j = 0; j < dim2; j++)
        {
            (*array)[i][j] = i+j;
        }
    }
    
    for (i = 0; i < dim1; i++)
    {
        for (j = 0; j < dim2; j++)
        {
            printf("%f \n", (*array)[i][j]);
        }
    }

    free(*array);
    return 0;
}
