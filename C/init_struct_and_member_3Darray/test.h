#include <stdio.h>
#include <stdlib.h>

struct coord *coordAlloc(int nPos, int nPos1, int nPos2);

void coordFree(struct coord *coord);

struct coord
{
    int     nPos;
    int     nPos1;
    int     nPos2;
    double*** x;
};
