#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "mpi.h"

bool hit(double x, double y, double z);
bool sphere(double x, double y, double z, double[] center);

int main(int argc, char **argv)
{
    // R,X,Y,X
    double[][] = {
        {0.1, 0.1, 0.2, 0.3},
        {0.1, 1.1, 1.2, 1.3},
        {0.1, 2.1, 2.2, 2.3}};

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

    int left_edge = rank + 1 == size
                        ? (rank + 1) * interval_size + N % size + 1
                        : (rank + 1) * interval_size;

    for (int i = rank * interval_size; i < left_edge; i++)
    {
        for(int j = 0; j< )
    }

    if (rank + 1 != size)
    {
        MPI_Send(&n, 1, MPI_INT, size - 1, 10, MPI_COMM_WORLD);
    }
    else
    {
        int resunlt_n = 0;
        int buf;
        MPI_Status status;
        for (int r = 0; r < size - 1; r++)
        {
            MPI_Recv(&buf, N, MPI_INT, r, 10, MPI_COMM_WORLD, &status);
            resunlt_n += buf;
        }

        printf("resunlt_n = %d\n", resunlt_n);
    }
    MPI_Finalize();
}

bool hit(double x, double y, double z, double[][] atoms, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (sphere(x, y, z, atoms[i]))
        {
            return true;
        }
    }
    return false;
}

bool sphere(double x, double y, double z, double[] center)
{
    return (x - center[1]) * (x - center[1]) +
               (y - center[2]) * (y - center[2]) +
               (z - center[3]) * (z - center[3]) <=
           center[0];
}