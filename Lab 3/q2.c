#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

double compute_average(int *arr, int M) {
    int sum = 0;
    for (int i = 0; i < M; i++) {
        sum += arr[i];
    }
    return (double)sum / M;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int N, M; 
    int *arr = NULL;
    int *sub_array = NULL;
    double *averages = NULL;
    double total_sum = 0;
    double total_average = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    N = size;


    if (rank == 0) {
        printf("Enter the number of elements per process (M): ");
        scanf("%d", &M);
        
        arr = (int *)malloc(N * M * sizeof(int)); 
        averages = (double *)malloc(N * sizeof(double)); 


        printf("Enter the %d * %d elements:\n", N, M);
        for (int i = 0; i < N * M; i++) {
            scanf("%d", &arr[i]);
        }
    }


    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    sub_array = (int *)malloc(M * sizeof(int));
    MPI_Scatter(arr, M, MPI_INT, sub_array, M, MPI_INT, 0, MPI_COMM_WORLD);

    double avg = compute_average(sub_array, M);
    printf("Average of process: %d = %f",rank, avg);
    MPI_Gather(&avg, 1, MPI_DOUBLE, averages, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            total_sum += averages[i];
        }
        total_average = total_sum / N;

        printf("The total average of all elements is: %.2f\n", total_average);

        free(arr);
        free(averages);
    }

    free(sub_array);

    MPI_Finalize();
    
    return 0;
}

