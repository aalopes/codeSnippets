// Hack to store VLA in struct as void pointer and typecasting

// Useful to store VLA in a struct and pass it to functions expecting VLAs
// This should work as well if the VLA is stored on the heap, using malloc.
// Do not forget, however, that as soon as VLAs go out of scope, they are deallocated.
// It shouldn't make much trouble, however, if you declare them in the main function.
// Note that double ** and double (*)[dim2] are different types! So do not even attempt
// to mix these two types. It won't work! (just because you access their elements 
// using the same notation, i.e. a[i][j], they are not identical objects!).

// Of course you can, if you believe it acts as some sort of documentation,
// declare array.data as (double **), and typecaset arrayVLA to double **, 
// but do note that if you try to dereference the pointer before typecasting it
// even though you use the same notation a[i][j], it will not work, as stated above.

#include <stdio.h>
#include <stdlib.h>

struct array
{
    int dim1;
    int dim2;
    void *data;
};

/* wrapper function to function accepting a VLA */
int wrapperPrintf(struct array *array)
{
    arrayPrintf(array->dim1, 
                array->dim2,
                (double (*)[array->dim2])array->data
                );

    return 0;
}

/* a function accepting a VLA */
int arrayPrintf(int dim1, int dim2, double  array[dim1][dim2] )
{
    int i,j;
    for (i = 0; i < dim1; i++)
    {
        for (j = 0; j < dim2; j++)
        {
           printf("%f \n", array[i][j]);
        }
    }

    return 0;
}


int main()
{
    int dim1  = 20;
    int dim2  = 4;
    int i, j;
    double arrayVLA[dim1][dim2];

    struct array array;
    array.dim1 = dim1;
    array.dim2 = dim2;
    array.data = arrayVLA; /* automatic cast to void* */

    /* fill VLA */
    for (i = 0; i < dim1; i++)
    {
        for (j = 0; j < dim2; j++)
        {
           arrayVLA[i][j] = i+j;
        }
    }


    /* alternatively */
    /*
    for (i = 0; i < dim1; i++)
    {
        for (j = 0; j < dim2; j++)
        {
           ( (double (*)[dim2]) (array.data) )[i][j] = i+j;
        }
    }
    */
    wrapperPrintf(&array);

    return 0;
}
