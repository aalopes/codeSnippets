#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Each thread will perform a very basic computation
   The total number of threads can be changed by changing the 
   N_THREADS macro and the size of the iterating loop with 
   N_LOOP. Since sin is periodic with average 0, it shouldn't
   overflow  (but that depends obviously on the sampling).
   Allocation will be made on the heap to avoid stack overflows. */

#define N_THREADS 4
#define N_LOOP    10000000

void *thread(void *arg)
{
    int i;
    double calc = 0.0;

    for(i = 0; i < N_LOOP; i++)
    {
        calc = calc + sin(i); 
    }

}

int main(int argc, char *argv[])
{
    int i, ret;
    struct timespec t_init_wall, t_end_wall;
    double elapsed_wall, elapsed_cpu;
    clock_t t_init_cpu, t_end_cpu;

    /* begin timing */
    clock_gettime(CLOCK_MONOTONIC, &t_init_wall);
    t_init_cpu = clock();

    /* create array of threads id */
    pthread_t thr_id[N_THREADS];

    /* create  threads */
    for(i = 0; i < N_THREADS; i++)
    {
        ret = pthread_create(&thr_id[i], NULL, thread, NULL);
        if (ret)
        {
            printf("ERROR: return code is %d\n", ret);
            exit(-1);
        }
    }
    printf("All threads started!\n");

    /* block main until threads complete */
    for(i = 0; i < N_THREADS; i++)
    {
       ret = pthread_join(thr_id[i], NULL);

        if (ret)
        {
            printf("ERROR: return code is %d\n", ret);
            exit(-1);
        }
    }

    /* end timing */
    t_end_cpu = clock();
    clock_gettime(CLOCK_MONOTONIC, &t_end_wall);

    /* calculate elapsed time */
    elapsed_cpu =   (double)(t_end_cpu - t_init_cpu) / CLOCKS_PER_SEC;
    elapsed_wall =  (t_end_wall.tv_sec - t_init_wall.tv_sec);
    elapsed_wall += (t_end_wall.tv_nsec - t_init_wall.tv_nsec) / 1000000000.0; 

    printf("Total number of operations: %g\n", (double) N_THREADS*N_LOOP);
    printf("Total wall-time: %g s\n", elapsed_wall);
    printf("Total cpu-time:  %g s\n", elapsed_cpu);

    pthread_exit(NULL);
    return 0;
}
