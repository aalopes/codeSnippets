// Example of the allocation of a structure and its members, for a structure containing a 3D dynamic array.
// These are not Iliffle vectors - the data is all in a contiguous memory block.

// Although several calls to malloc are needed to store several arrays of pointers,
// the heap fragmentation will be smaller than if we just call malloc recursively for
// all dimensions.

// See <http://stackoverflow.com/questions/13224113/using-a-pointer-to-a-dynamic-2d-array-within-a-struct>
// See <http://stackoverflow.com/questions/917783/how-do-i-work-with-dynamic-multi-dimensional-arrays-in-c>
// See <https://en.wikipedia.org/wiki/C_syntax#Multidimensional_arrays>

// Alexandre Lopes

#include "test.h"

struct coord *coordAlloc (int nPos, int nPos1, int nPos2) 
{
    double* data; /* data array */
    double*** x;
    int i, j;

    /* try to allocate structure */
    struct coord *retVal = malloc (sizeof (struct coord));
    if (retVal == NULL)
    {
        return NULL; 
    }
    
    /* try to allocate member and free structure if it fails */
    /* allocate rows */
    x = malloc (nPos *  sizeof (double**)); 
    if (x == NULL)
    { 
        free (retVal); 
        return NULL; 
    }
    else
    {

        /* allocate 2nd dimension */
        for (i = 0; i < nPos; i++)
        {
            x[i] = malloc (nPos1 * sizeof(double *));

            // if allocation failed, roll back
            if (x[i] == NULL)
            {
                for (j = 0; j < i; j++)
                {
                    free(x[j]);
                    free(x);
                    free(retVal);
                    return NULL;
                }
            }
            
        }
        data      = malloc(nPos*nPos1*nPos2* sizeof(double));
        // if allocation failed, deallocate everything
        if (data == NULL)
        {
            for (i = 0; i < nPos; i++)
            {
                free(x[i]);
            }
            free(x);
            free(retVal);
            return NULL;
        }
        else
        {
            /* point to data */
            for (i = 0; i < nPos; i++)
            {

                for (j = 0; j < nPos1; j++)
                {
                     x[i][j] = (data + (i * nPos1 *nPos2) + (j * nPos2));
                }
            }
        }
    }
    retVal->x = x;

    /* set non-dynamic members */
    retVal->nPos  = nPos;
    retVal->nPos1 = nPos1;
    retVal->nPos2 = nPos2;

    return retVal;
}

void coordFree (struct coord *coord) 
{
    int i;

    // structure is either NULL or fully built
    if (coord != NULL)
    {
        free(coord->x[0][0]); // our data array above
        for (i = 0; i < coord->nPos; i++ )
        {
            free(coord->x[i]);
        }
        free (coord->x);
        free (coord);
    }
}

int main()
{
    int nPos  = 10;
    int nPos1 = 20;
    int nPos2 = 30;
    int i, j, k;

    /* allocate struct and member arrays */
    struct coord * coord = coordAlloc(nPos, nPos1 , nPos2);

    for (i = 0; i < nPos; i++)
    {
        for (j = 0; j < nPos1; j++)
        {
            for(k = 0; k < nPos2; k++)
            {
                coord->x[i][j][k] = i+j+k;
            }
        }
    }
    
    for (i = 0; i < nPos; i++)
    {
        for (j = 0; j < nPos1; j++)
        {

            for (k = 0; k < nPos2; k++)
            {
                printf("%f \n", coord->x[i][j][k]);
            }
        }
    }
    //coordFree (coord);
    return 0;
}
