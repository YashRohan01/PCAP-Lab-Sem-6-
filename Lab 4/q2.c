#include <stdio.h>
#include <mpi.h>

#define N 3  // Size of the matrix (3x3)

int main(int argc, char *argv[]) {
    int rank, size;
    int matrix[N][N], local_matrix[N][N];
    int element, local_count = 0, global_count = 0;
    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    if (rank == 0) {
        printf("Enter a 3x3 matrix:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }

        printf("Enter the element to search for: ");
        scanf("%d", &element);
    }

    MPI_Bcast(&element, 1, MPI_INT, 0, comm);
    MPI_Bcast(matrix, N * N, MPI_INT, 0, comm);

    int rows_per_process = N / size;  // In this case, size = 3, so each process gets 1 row
    MPI_Scatter(matrix, N * rows_per_process, MPI_INT, local_matrix, N * rows_per_process, MPI_INT, 0, comm);

    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < N; j++) {
            if (local_matrix[i][j] == element) {
                local_count++;
            }
        }
    }

    MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, comm);

    if (rank == 0) {
        printf("The element %d appears %d times in the matrix.\n", element, global_count);
    }

    MPI_Finalize();

    return 0;
}

