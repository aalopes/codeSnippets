#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N_FORKS 4
#define N_LOOP 100000000

main(int argc, char *argv[]) 
{
    struct timespec t_init_wall, t_end_wall;
    double elapsed_wall, elapsed_cpu;
    clock_t t_init_cpu, t_end_cpu;
    int i;
    pid_t pid;

    double *a = malloc(sizeof(double)* N_LOOP);

    /* begin timing */
    clock_gettime(CLOCK_MONOTONIC, &t_init_wall);
    t_init_cpu = clock();

    for(i = 0; i < N_FORKS; i++)
    {
        pid = fork();
        /* fork failed */
        if (pid == -1)
        {
            printf("Fork failed!\n");
            exit(-1);
        }

        /* I'm a child - don't loop! */
        if (pid == 0)
        {
            break;
        }
    }

    for(i = 0; i < N_LOOP; i++)
    {
        a[i] = log(exp( (double) i));
    }

    /* end timing */
    t_end_cpu = clock();
    clock_gettime(CLOCK_MONOTONIC, &t_end_wall);

    /* calculate elapsed time */
    elapsed_cpu  =  (double)(t_end_cpu - t_init_cpu) / CLOCKS_PER_SEC;
    elapsed_wall =  (t_end_wall.tv_sec - t_init_wall.tv_sec);
    elapsed_wall += (t_end_wall.tv_nsec - t_init_wall.tv_nsec) / 1000000000.0; 

    /* TBD - open shared memory and output only the time of the process that
       takes the longest to complete - that should be our number */
    printf("Total number of operations: %g\n", (double) N_FORKS*N_LOOP);
    printf("Total wall-time: %g s\n", elapsed_wall);
    printf("Total cpu-time:  %g s\n", elapsed_cpu);

    return 0;
}
