#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	int rank, size;
	int value;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(rank == 0){
		printf("Enter the value: ");
		scanf("%d", &value);
		value++;
		MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else{
		MPI_Recv(&value, 1, MPI_INT, rank - 1, 0 , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		value++;
		printf("\nProcess %d received value: %d: %d\n", rank,value-1);
		if (rank < size - 1) {
            		MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            		printf("Process %d sent value: %d to process %d\n", rank, value, rank + 1);
        	} 
        	else {
            		MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            		printf("Process %d sent value: %d back to root\n", rank, value);
        	}
	}
	
	if (rank == 0) {
        	MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        	printf("Root process (rank 0) received final value: %d\n", value);
    	}
	
	MPI_Finalize();
	return 0;
}
