#include"mpi.h"
#include<stdio.h>

int factorial(int n){
	int factorial = 1;
	while(n > 0){
		factorial = factorial * n;
		n = n - 1;
	}
	return factorial;
}

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]){
	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int output;
	if (rank % 2 == 0){
		output = factorial(rank);
	}
	else{
		output = fibonacci(rank);
	}
	printf("Rank = %d & Output = %d\n",rank,output);
	return 0;
}
