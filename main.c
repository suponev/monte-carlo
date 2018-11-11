#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //printf("size = %lf\n", size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double h = 0.001;
    int x, y, z;
    int N = 20;
    int n = 1;

    int interval_size = (int)(N / size);
    printf("N/size = %d\n", interval_size);
    int left_edge = rank + 1 == size
                        ? (rank + 1) * interval_size + N % size + 1
                        : (rank + 1) * interval_size;

    for (int i = rank * interval_size; i < left_edge; i++)
    {
        printf("rank = %d : x = %d\n", rank, i);
        // x = i;
    }

    if (rank + 1 != size)
    {
        MPI_Send(&n, 1, MPI_INT, size - 1, 10, MPI_COMM_WORLD);
       // MPI_Barrier(MPI_COMM_WORLD);
    }
    else
    {
        //MPI_Barrier(MPI_COMM_WORLD);
        int resunlt_n = 0;
        int buf;
        MPI_Status status;
        for (int r = 0; r < size - 1; r++)
        {
            MPI_Recv(&buf, N, MPI_INT,r, 10, MPI_COMM_WORLD, &status);
            resunlt_n += buf;
        }

        printf("resunlt_n = %d\n", resunlt_n);
    }
    MPI_Finalize();
}
