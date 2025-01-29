#include"mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]){
	int x = 10, y = 15;
	int rank,size;
	
	MPI_Init(&argc, &argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	switch(rank){
		case 0:
			printf("Rank = %d . Expression = 'x+y' .Result = %d\n",rank, x+y);
			break;
		case 1:
			printf("Rank = %d . Expression = 'x-y' .Result = %d\n",rank, x-y);
			break;
		case 2:
			printf("Rank = %d . Expression = 'x*y' . Result = %d\n",rank, x*y);
			break;
		case 3:
			printf("Rank = %d . Expression = 'x/y' . Result = %f\n",rank, x/y);
			break;
		default:
			printf("Rank = %d . Out of Bounds of the 4 Operations\n",rank);
			break;
	}
	return 0;
}
