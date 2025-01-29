#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define N 4 // Size of the matrix (4x4)

int main(int argc, char* argv[]) {
    int rank, size;
    int matrix[N][N];
    int local_row[N];
    
    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        if (rank == 0) {
            printf("This program requires exactly 4 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        // Root process: Input the 4x4 matrix
        printf("Enter the 4x4 matrix:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }
    }

    // Broadcast the entire matrix to all processes
    MPI_Bcast(matrix, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process works on a specific row based on rank
    for (int i = 0; i < N; i++) {
        local_row[i] = matrix[rank][i]; // Get the row corresponding to the rank
    }

    // Perform the addition operation based on the rank
    if (rank == 1) {
        // Add first row to second row
        for (int i = 0; i < N; i++) {
            local_row[i] += matrix[0][i];
        }
    } else if (rank == 2) {
        // Add first row and second row to third row
        for (int i = 0; i < N; i++) {
            local_row[i] += matrix[0][i] + matrix[1][i];
        }
    } else if (rank == 3) {
        // Add first, second, and third rows to fourth row
        for (int i = 0; i < N; i++) {
            local_row[i] += matrix[0][i] + matrix[1][i] + matrix[2][i];
        }
    }

    // Gather the updated rows back to the root process
    MPI_Gather(local_row, N, MPI_INT, matrix, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Root process: Output the modified matrix
    if (rank == 0) {
        printf("\nModified matrix:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

