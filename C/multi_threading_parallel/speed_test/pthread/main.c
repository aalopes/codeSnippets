#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Each thread will perform a very basic computation
   The total number of threads can be changed by changing the 
   N_EXTRA_THREADS macro and the size of the iterating loop with 
   N_LOOP.  */

/* number of threads actually + 1 with the main thread */
#define N_EXTRA_THREADS 7
#define N_LOOP    20000000

void *thread(void *arg)
{
    int i;
    double * res = (double *) arg;

    for(i = 0; i < N_LOOP; i++)
    {
        *res += sin(M_PI*(1+4*i)/2);
    }

    /* valgrind may indicate leak with this */
    /* known bug and not dangerous  */
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int i, ret;
    struct timespec t_init_wall, t_end_wall;
    double elapsed_wall, elapsed_cpu;
    clock_t t_init_cpu, t_end_cpu;
    double thr_ret[N_EXTRA_THREADS];
    double res = 0;

    /* begin timing */
    clock_gettime(CLOCK_MONOTONIC, &t_init_wall);
    t_init_cpu = clock();

    /* create array of threads id */
    pthread_t thr_id[N_EXTRA_THREADS];

    /* create  threads  each thread gets the address of a double for output */
    for(i = 0; i < N_EXTRA_THREADS; i++)
    {
        ret = pthread_create(&thr_id[i], NULL, thread, (void *)&thr_ret[i]);
        if (ret)
        {
            printf("ERROR: return code is %d\n", ret);
            exit(-1);
        }
    }
    printf("All threads started!\n");

    /* main thread calculation */
    for(i = 0; i < N_LOOP; i++)
    {
        res += sin(M_PI*(1+4*i)/2);
    }

    /* block main until threads complete - sum return */
    for(i = 0; i < N_EXTRA_THREADS; i++)
    {
       ret = pthread_join(thr_id[i], NULL);

        if (ret)
        {
            printf("ERROR: return code is %d\n", ret);
            exit(-1);
        }
        res += thr_ret[i];
    }

    /* sum results - tbd */

    /* end timing */
    t_end_cpu = clock();
    clock_gettime(CLOCK_MONOTONIC, &t_end_wall);

    /* calculate elapsed time */
    elapsed_cpu =   (double)(t_end_cpu - t_init_cpu) / CLOCKS_PER_SEC;
    elapsed_wall =  (t_end_wall.tv_sec - t_init_wall.tv_sec);
    elapsed_wall += (t_end_wall.tv_nsec - t_init_wall.tv_nsec) / 1000000000.0; 

    printf("Result: %g\n", res);
    printf("Total number of operations: %g\n", (double) (N_EXTRA_THREADS+1)*N_LOOP);
    printf("Total wall-time: %g s\n", elapsed_wall);
    printf("Total cpu-time:  %g s\n", elapsed_cpu);

    pthread_exit(NULL);
    return 0;
}
