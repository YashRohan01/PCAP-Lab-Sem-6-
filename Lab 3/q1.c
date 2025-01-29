#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int factorial(int n){
	int factorial = 1;
	for (int i = 1; i <= n; i++){
		factorial *= i;
	}
	return factorial;
}

int main(int argc, char *argv[]){
	int rank, size;
	int N;
	int *values = NULL;
	int *factorials = NULL;
	int sum = 0;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if (rank == 0){
		printf("Enter the number of values (N)");
		scanf("%d", &N);
		values = (int *) malloc(N * sizeof(int));
		factorials = (int *)malloc(N * sizeof(int));
		printf("Enter the %d values: \n",N);
		for(int i = 0; i < N; i++){
			scanf("%d",&values[i]);
		}
	}
	
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	int value = 0; 
	if (rank < N){
		MPI_Scatter(values, 1, MPI_INT, &value, 1, MPI_INT, 0, MPI_COMM_WORLD);
	}
	int fact = 1; 
	if (rank < N){
		fact = factorial(value);
		printf("Rank %d sends %d.\n",rank, fact);
	}
	MPI_Gather(&fact, 1, MPI_INT, factorials, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	if (rank == 0){
		for(int i = 0; i < N; i++){
			sum+=factorials[i];
		}
		printf("Sum of factorials = %d\n",sum);
	}
	
	if (rank == 0) {
        free(values);
        free(factorials);
    }
	MPI_Finalize();
	return 0;
}
