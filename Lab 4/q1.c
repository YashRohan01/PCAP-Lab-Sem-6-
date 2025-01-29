#include <stdio.h>
#include "mpi.h"

int factorial(int n){
	int factorial = 1;
	for (int i = n; i >= 1; i--){
		factorial *= i; 
	}
	return factorial;
}

int main(int argc, char *argv[]){
	int rank, size;
	int sendbuf, recvbuf;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	sendbuf = factorial(rank);
	MPI_Scan(&sendbuf, &recvbuf, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);	
	
	printf("Process %d: Local value = %d, Cumulative sum = %d\n", rank, sendbuf, recvbuf);
	MPI_Finalize();
	return 0;
}

