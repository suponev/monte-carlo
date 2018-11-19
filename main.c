#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "mpi.h"

#define DIM1 3
#define DIM2 4

bool hit(float x, float y, float z, float **atoms, int count);
bool sphere(float x, float y, float z, float *center);

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);
    double starttime, endtime;
    starttime = MPI_Wtime();
    float atoms[DIM1 * DIM2];
    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        FILE *file;
        file = fopen("input", "r");
        for (int i = 0; i < DIM1 * DIM2; i++)
        {
            fscanf(file, "%f", &atoms[i]);
            printf("%lf\n", atoms[i]);
        }
    }

    MPI_Bcast(&atoms[0], DIM1 * DIM2, MPI_FLOAT, 0, MPI_COMM_WORLD);

    float h = 0.01;
    float X_MIN, X_MAX, Y_MIN, Y_MAX, Z_MIN, Z_MAX, R;
    R = atoms[0];
    X_MIN = atoms[1] - R;
    X_MAX = atoms[1] + R;
    Y_MIN = atoms[2] - R;
    Y_MAX = atoms[2] + R;
    Z_MIN = atoms[3] - R;
    Z_MAX = atoms[3] + R;

    for (int i = 0; i < DIM1 * DIM2; i = i + DIM2)
    {
        R = atoms[i];
        X_MAX = atoms[i + 1] + R > X_MAX ? atoms[i + 1] + R : X_MAX;
        X_MIN = atoms[i + 1] - R < X_MIN ? atoms[i + 1] - R : X_MIN;
        Y_MAX = atoms[i + 2] + R > Y_MAX ? atoms[i + 2] + R : Y_MAX;
        Y_MIN = atoms[i + 2] - R < Y_MIN ? atoms[i + 2] - R : Y_MIN;
        Z_MAX = atoms[i + 3] + R > Z_MAX ? atoms[i + 3] + R : Z_MAX;
        Z_MIN = atoms[i + 3] - R < Z_MIN ? atoms[i + 3] - R : Z_MIN;
    }

    if (rank == 0)
    {
        printf("X_MIN = %lf X_MAX = %lf\n", X_MIN, X_MAX);
        printf("Z_MIN = %lf Z_MAX = %lf\n", Y_MIN, Y_MAX);
        printf("Y_MIN = %lf Y_MAX = %lf\n", Z_MIN, Z_MAX);
    }

    int n = 0;
    int X_ITER_COUNT = (int)((X_MAX - X_MIN) / h);
    int INTERVAL = X_ITER_COUNT / size;
    int right_edge = rank + 1 == size
                         ? (rank + 1) * INTERVAL + X_ITER_COUNT % size + 1
                         : (rank + 1) * INTERVAL;
    float x, y, z;
    for (int i = rank * INTERVAL; i < right_edge; i++)
    {
        x = X_MIN + i * h;
        for (int j = 0; j < (Y_MAX - Y_MIN) / h; j++)
        {
            y = Y_MIN + j * h;
            for (int k = 0; k < (Z_MAX - Z_MIN) / h; k++)
            {
                z = Z_MIN + k * h;
                // Определение попадания
                for (int i = 0; i < DIM1 * DIM2; i = i + DIM2)
                {
                    if ((x - atoms[i + 1]) * (x - atoms[i + 1]) +
                            (y - atoms[i + 2]) * (y - atoms[i + 2]) +
                            (z - atoms[i + 3]) * (z - atoms[i + 3]) <=
                        atoms[i] * atoms[i])
                    {
                        n++;
                        break;
                    }
                }
            }
        }
    }

    if (rank != 0)
    {
        MPI_Send(&n, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }
    else
    {
        int resunlt_n = n;
        int buf;
        MPI_Status status;

        for (int r = 1; r < size; r++)
        {
            MPI_Recv(&buf, 1, MPI_INT, r, 10, MPI_COMM_WORLD, &status);
            resunlt_n += buf;
        }
        float V_CUBE = (X_MAX - X_MIN) * (Y_MAX - Y_MIN) * (Z_MAX - Z_MIN);
        float ALL_ITER = V_CUBE / h / h / h;
        endtime = MPI_Wtime();
        printf("All iter =  %f\n", ALL_ITER);
        printf("V cube = %f\n", V_CUBE);
        printf("All hit = %d\n", resunlt_n);
        printf("V (m^(-30)) = %f\n", resunlt_n / ALL_ITER * V_CUBE);

        printf("That took %f seconds\n", endtime - starttime);
    }
    MPI_Finalize();
}
