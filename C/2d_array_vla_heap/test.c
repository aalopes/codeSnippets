// 'Heap allocated' VLA (variable length-array) - actually the VLA 
// here is a pointer of type double(*)[dim2], and still allocated on the 
// stack.
// This is a C99 standard!

// Note that this works as well for usual C arrays with compile-time
// fixed size since their types are identical to the type of VLAs
// (which is not a double ** for 2D arrays which is what one usually gets
//  using the usual dynamic allocation ).

// The advantage of using VLAs vs usual dynamically allocated arrays
// is that it is very easy to extend it to high dimensions while using
// the square bracket dereference notation, whithout having to code
// anything complicated and doing index-gymnastics...

// Alexandre Lopes

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int dim1  = 5;
    int dim2  = 20;
    int i, j;
    
    // the type of the pointer is double(*)[dim2]
    // contrast this with the usual dynamic allocation, which
    // would result into a type double **.

    double (*array)[dim2] = malloc(sizeof(array) * dim1 * dim2); 

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

    free(array);
    return 0;
}
