#include"mpi.h"
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char *argv[]){
	char name[] = "YASH";
	int rank,size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	/*switch(name[rank]){
		case >='a'&& <='z':
			name[rank] = name[rank] - 32;
			break;
		case >='A' && <='Z':
			name[rank] = name[]
			break;
	}*/
	
	if(rank < strlen(name)){
		if(isupper(name[rank])){
			name[rank] = tolower(name[rank]);
			printf("Modified string for rank = %d : %s\n",rank,name);
		}
		else{
			name[rank] = toupper(name[rank]);
			printf("Modified string for rank = %d : %s\n",rank,name);
		}
	}
	else{
		printf("Rank out of bounds of the string length\n");
	}
	
	return 0;
	
}
