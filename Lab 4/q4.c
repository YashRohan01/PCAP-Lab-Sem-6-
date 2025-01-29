#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MAX_LEN 100

int main(int argc, char *argv[]) {
    int rank, size;
    char word[MAX_LEN], local_word[MAX_LEN];
    char output_word[MAX_LEN * MAX_LEN];  // to hold the final result (worst case size)
    int N;

    MPI_Comm comm = MPI_COMM_WORLD;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    if (rank == 0) {
        printf("Enter a word: ");
        scanf("%s", word);  
        N = strlen(word);  
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, comm);
    MPI_Bcast(word, N, MPI_CHAR, 0, comm);


    if (rank < N) {
        int repeat_count = rank + 1; 
        for (int i = 0; i < repeat_count; i++) {
            local_word[i] = word[rank];
        }
        local_word[repeat_count] = '\0';  
    } else {
        local_word[0] = '\0'; 
    }

    MPI_Gather(local_word, MAX_LEN, MPI_CHAR, output_word, MAX_LEN, MPI_CHAR, 0, comm);

    if (rank == 0) {
        printf("Output word: ");
        for (int i = 0; i < N; i++) {
            printf("%s", &output_word[i * MAX_LEN]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

