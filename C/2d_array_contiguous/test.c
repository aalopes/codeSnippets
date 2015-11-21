// Heap allocated contigous 2D array using double ** pointer
// Since there are only two calls to malloc, this will not result in heap fragmentation.

// See <http://stackoverflow.com/questions/917783/how-do-i-work-with-dynamic-multi-dimensional-arrays-in-c>
// See <https://en.wikipedia.org/wiki/C_syntax#Multidimensional_arrays>

// Alexandre Lopes

#include <stdio.h>
#include <stdlib.h>

double** arrayAlloc2D (int dim1, int dim2) 
{
    double* data;   /* pointer to data array */
    double** array; /* pointer to array of pointers pointing to data array */
    int i;

    /* allocate rows */
    array = malloc (dim1 *  sizeof (*array)); 
    if (array == NULL)
    { 
        return NULL; 
    }
    else
    {
        data      = malloc(dim1*dim2* sizeof(**array));
        if (data == NULL)
        {
            free (array);
            return NULL;
        }
        else
        {
            /* allocate columns */
            for (i = 0; i < dim1; i++)
            {
                array[i] = (data + (i * dim2));
            }
        }
    }

    return array;
}

void arrayFree2D (double **array) 
{
    /* if array is built the array it points to is also built*/
    if (array != NULL)
    {
        free (array[0]); /* columns */
        free (array);    /* rows */
    }
}

int main()
{
    int dim1  = 10;
    int dim2  = 20;
    int i, j;
    
    double **array = arrayAlloc2D (dim1, dim2);

    for (i = 0; i < dim1; i++)
    {
        for (j = 0; j < dim2; j++)
        {
            array[i][j] = i+j;
        }
    }
    
    for (i = 0; i < dim1; i++)
    {
        for (j = 0; j < dim2; j++)
        {
            printf("%f \n", array[i][j]);
        }
    }
    arrayFree2D (array);
    return 0;
}
