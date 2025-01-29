#include"mpi.h"
#include<stdio.h>
#include<math.h>

int main(int argc, char *argv[]){
	int rank, size;
	int x = 5;
	// Initialize the MPI environment
	MPI_Init(&argc, &argv);
	
	// Get the rank of the process (unique ID for each process)
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// Get the total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	double result = pow(x,rank);
	
	printf("Process %d of %d : pow(%d,%d) = %f\n",rank,size,x,rank,result);
	
	MPI_Finalize();
	return 0;
}
