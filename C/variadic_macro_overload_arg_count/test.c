// Variadic macro argument counting and overloading

// This specific example is meant to provide a simple interface for allocating
// VLAs on the heap. It comes also with a sample code.
// References: 

// <http://stackoverflow.com/questions/5365440/variadic-macro-trick>
// <http://efesx.com/2010/07/17/variadic-macro-to-count-number-of-arguments/>

// This only works for 7 arguments, but can be expanded

// Alexandre Lopes

#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1)

#define ALLOCATE_IMPL2(count, ...) ALLOCATE ## count (__VA_ARGS__)
#define ALLOCATE_IMPL(count, ...) ALLOCATE_IMPL2(count, __VA_ARGS__) 
#define ALLOCATE(...) ALLOCATE_IMPL(VA_NARGS(__VA_ARGS__), __VA_ARGS__)

#define ALLOCATE1(ARRAY) 
#define ALLOCATE2(ARRAY, DIM1) double (*ARRAY) = malloc((sizeof *ARRAY) * DIM1);
#define ALLOCATE3(ARRAY, DIM1, DIM2) double (*ARRAY)[DIM2] = malloc((sizeof *ARRAY) * DIM1 * DIM2);
#define ALLOCATE4(ARRAY, DIM1, DIM2, DIM3) double (*ARRAY)[DIM2][DIM3] = malloc((sizeof *ARRAY) * DIM1 * DIM2 * DIM3);
#define ALLOCATE5(ARRAY, DIM1, DIM2, DIM3, DIM4) double (*ARRAY)[DIM2][DIM3][DIM4] = malloc((sizeof *ARRAY) * DIM1 * DIM2 * DIM3 * DIM4);
#define ALLOCATE6(ARRAY, DIM1, DIM2, DIM3, DIM4, DIM5) double (*ARRAY)[DIM2][DIM3][DIM4][DIM5] = malloc((sizeof *ARRAY) * DIM1 * DIM2 * DIM3 * DIM4 * DIM5);
#define ALLOCATE7(ARRAY, DIM1, DIM2, DIM3, DIM4, DIM5, DIM6) double (*ARRAY)[DIM2][DIM3][DIM4][DIM5][DIM6] = malloc((sizeof *ARRAY) * DIM1 * DIM2 * DIM3 * DIM4 * DIM5 * DIM6);
#define ALLOCATE8(ARRAY, DIM1, DIM2, DIM3, DIM4, DIM5, DIM6, DIM7) double (*ARRAY)[DIM2][DIM3][DIM4][DIM5][DIM6][DIM7] = malloc((sizeof *ARRAY) * DIM1 * DIM2 * DIM3 * DIM4 * DIM5 * DIM6 * DIM7);

#include <stdio.h>
#include <stdlib.h>

int main(){
    int dim1, dim2, dim3;
    int i, j, k;

    dim1 = 5;
    dim2 = 5;
    dim3 = 5;

    // allocate VLA on the heap
    ALLOCATE(array,dim1,dim2,dim3)

    // fill in array
    for ( i = 0; i < dim1; i++) 
    {
        for ( j = 0; j < dim1; j++) 
        {
            for ( k = 0; k < dim1; k++) 
            {
                array[i][j][k] = i+j+k;
            }
        }
    }

    // print result

    for ( i = 0; i < dim1; i++) 
    {
        for ( j = 0; j < dim1; j++) 
        {
            for ( k = 0; k < dim1; k++) 
            {
                printf("%f \n", array[i][j][k]);
            }
        }
    }

    return 0;
}
