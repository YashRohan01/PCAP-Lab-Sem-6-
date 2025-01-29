#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>


void alternate_strings(char *s1, char *s2, char *result, int portion_size) {
    for (int i = 0; i < portion_size; i++) {
        result[2 * i] = s1[i];   
        result[2 * i + 1] = s2[i]; 
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    char *S1 = NULL, *S2 = NULL, *result = NULL;
    int string_length, portion_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Root process reads the strings
    if (rank == 0) {

	string_length = size;
        S1 = (char *)malloc((string_length + 1) * sizeof(char));
        S2 = (char *)malloc((string_length + 1) * sizeof(char));
        result = (char *)malloc((2 * string_length + 1) * sizeof(char)); // Resultant string will be twice the length

        printf("Enter string S1: ");
        scanf("%s", S1);
        printf("Enter string S2: ");
        scanf("%s", S2);

        // Ensure that the string length is divisible by the number of processes
        if (string_length % size != 0) {
            printf("Error: The string length is not divisible by the number of processes.\n");
            MPI_Finalize();
            return -1;
        }
    }

    MPI_Bcast(&string_length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    portion_size = string_length / size;


    char *portion_s1 = (char *)malloc((portion_size + 1) * sizeof(char));
    char *portion_s2 = (char *)malloc((portion_size + 1) * sizeof(char));

    MPI_Scatter(S1, portion_size, MPI_CHAR, portion_s1, portion_size, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(S2, portion_size, MPI_CHAR, portion_s2, portion_size, MPI_CHAR, 0, MPI_COMM_WORLD);


    char *partial_result = (char *)malloc((2 * portion_size + 1) * sizeof(char));


    alternate_strings(portion_s1, portion_s2, partial_result, portion_size);


    MPI_Gather(partial_result, 2 * portion_size, MPI_CHAR, result, 2 * portion_size, MPI_CHAR, 0, MPI_COMM_WORLD);


    if (rank == 0) {
        result[2 * string_length] = '\0';  // Null-terminate the resultant string
        printf("S1 = %s\n", S1);
        printf("S2 = %s\n", S2);
        printf("Resultant = %s\n", result);


        free(S1);
        free(S2);
        free(result);
    }


    free(portion_s1);
    free(portion_s2);
    free(partial_result);


    MPI_Finalize();
    return 0;
}

