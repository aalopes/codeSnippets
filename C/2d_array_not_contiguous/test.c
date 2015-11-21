// Heap allocated 2D arrays using double ** pointers and Iliffle vectors
// This will result in heap fragmentation due to several calls to malloc.
//
// See <http://stackoverflow.com/questions/917783/how-do-i-work-with-dynamic-multi-dimensional-arrays-in-c>
// See <https://en.wikipedia.org/wiki/C_syntax#Multidimensional_arrays> 

// Alexandre Lopes

#include <stdio.h>
#include <stdlib.h>

double** array2dNcAlloc (int dim1, int dim2) 
{
    int i, j;
    double **array;

    /* allocate rows */
    array = malloc (dim1 *  sizeof ( *array )); 
    if (array == NULL)
    { 
        return NULL; 
    }
    else
    {
        // allocate columns
        for (i = 0; i < dim1; i++)
        {
            array[i] = malloc(dim2 * sizeof( **array  ));

            // if allocation failed
            if (array[i] == NULL)
            {
                // deallocate everything until now
                for ( j = 0; j < i; j++)
                {
                    free(array[j]);
                    free(array);
                }
            }
        }
    }

    return array;
}

void array2dNcFree (double **array, int dim1)
{
    int i;

    // if array is not NULL then its dereferences are also not
    for (i = 0; i < dim1; i++)
    {
        free (array[i]);
    }
    free (array);
}

int main()
{
    int dim1  = 50;
    int dim2  = 100;
    int i, j;

    // allocate array
    double **array = array2dNcAlloc(dim1, dim2);

    for (i = 1; i < dim1; i++)
    {
        for (j = 1; j < dim2; j ++)
        {
            array[i][j] = i*j;
        }
    }

    for (i = 1; i < dim1; i++)
    {
        for (j = 1; j < dim2; j ++)
        {
            printf("%f\n", array[i][j]);
        }
    }


    array2dNcFree (array, dim1);
    return 0;
}
