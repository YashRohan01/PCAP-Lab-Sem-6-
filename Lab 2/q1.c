#include "mpi.h"
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	char data[100] = "YashRohan";
	if(rank == 0){
		printf("Root Process sending the string: %s\n",data);
		MPI_Send(data, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
	}
	else if (rank == 1){
		MPI_Recv(data, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int i = 0;
		while(data[i] != '\0'){
			if(islower(data[i])){
				data[i] = toupper(data[i]);
			}
			else if (isupper(data[i])){
				data[i] = tolower(data[i]);
			}
			i++;
		}
		printf("Rank : %d recieved the string. Output string : %s\n",rank,data);
		MPI_Send(data, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}
	if(rank == 0){
        MPI_Recv(data, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Root Process received the toggled string: %s\n", data);
    }
	
	MPI_Finalize();
	return 0;
}
