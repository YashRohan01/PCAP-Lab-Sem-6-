#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int rank, size;
	
	MPI_Init(&argc, &argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int *data = NULL;
	int number;
	
	int *send_buffer = NULL;
    	int buffer_size = size * sizeof(int) + MPI_BSEND_OVERHEAD; 
	
	if (rank == 0){
		data = (int *)malloc(size* sizeof(int));
		send_buffer = (int *)malloc(buffer_size);
		
		printf("Enter the %d elements of the array: ",size);
		for (int i = 0; i < size; i++) {
            	printf("Enter value for element %d: ", i);
            	scanf("%d", &data[i]);
        	}
        	
        	MPI_Buffer_attach(send_buffer, buffer_size);
        	for (int i = 1; i < size; i++) {
            	MPI_Bsend(&data[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);  
        	}

        	number = data[0]; 
        	printf("Root process (rank 0) received: %d\n", number);

        	MPI_Buffer_detach(&send_buffer, &buffer_size);
	}
	else if (rank % 2 == 0){
        	MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        	int out = number*number;
        	printf("Process %d received value: %d\n", rank, out);
    	}
    	else{
    		MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        	int out = number*number*number;
        	printf("Process %d received value: %d\n", rank, out);
    	}
	
	MPI_Finalize();
	
	if(rank == 0){
		free(data);
	}
	return 0;
	
}
