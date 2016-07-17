#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/mman.h>

#define N_FORKS 7 /* N_FORKS + 1 processes  */
#define N_LOOP 20000000

int main(int argc, char *argv[]) 
{
    struct timespec t_init_wall, t_end_wall;
    double elapsed_wall, elapsed_cpu;
    clock_t t_init_cpu, t_end_cpu;
    int i;
    int child_id;
    int flag;
    double res;
    pid_t pid;

    /* finished is a flag - 
     * 0 if child finished calculation
     * 1 if not
     */
    struct child_data
    {
        int      res;
        int      finished;
    };

    /* memory to share with children */
    struct child_data *glob_data = mmap(NULL, N_FORKS*sizeof(struct child_data), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);

    /* initialize array structs*/
    for( i = 0; i < N_FORKS; i++)
    {
        glob_data[i].res      = 0;
        glob_data[i].finished = 0;

    }    

    /* variable for storing calculation results */
    double *a = malloc(sizeof(double)* N_LOOP);

    /* begin timing */
    clock_gettime(CLOCK_MONOTONIC, &t_init_wall);
    t_init_cpu = clock();

    for(child_id = 0; child_id < N_FORKS; child_id++)
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
        res += sin(M_PI*(1+4*i)/2 );
    }

    /* calculation finished, update shared memory - children only! */
    /* children return here */
    if (pid == 0)
    {
        glob_data[child_id].res      = res;
        glob_data[child_id].finished = 1;
        return 0;
    }
    else
    {
        /* wait for children to finish - check flags */
        for(;;)
        {
            flag = 0;
            for(i = 0; i < N_FORKS; i++)
            {
                flag += glob_data[i].finished;
            }
            if (flag == N_FORKS)
            {
                break;
            }
        }

        /* sum result */
        for(i = 0; i < N_FORKS; i++)
        {
            res += glob_data[i].res;
        }
        munmap(glob_data, N_FORKS*sizeof(struct child_data));

        /* end timing */
        t_end_cpu = clock();
        clock_gettime(CLOCK_MONOTONIC, &t_end_wall);

        /* calculate elapsed time */
        elapsed_cpu  =  (double)(t_end_cpu - t_init_cpu) / CLOCKS_PER_SEC;
        elapsed_wall =  (t_end_wall.tv_sec - t_init_wall.tv_sec);
        elapsed_wall += (t_end_wall.tv_nsec - t_init_wall.tv_nsec) / 1000000000.0; 

        printf("Result:  %g \n", res);
        printf("Total number of operations: %g\n", (double) (N_FORKS + 1)*N_LOOP);
        printf("Total wall-time: %g s\n", elapsed_wall);
        printf("Total cpu-time:  %g s\n", elapsed_cpu);

        return 0;
    }
}
