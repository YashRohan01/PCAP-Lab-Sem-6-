#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <stdbool.h>

bool is_vowel(char c) {
    char lower = c | ' ';
    return (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u');
}

int count_non_vowels(const char *str, int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (!is_vowel(str[i])) {
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    int rank, size;
    char *str = NULL;
    int N; 
    int string_length;
    int *non_vowel_counts = NULL; 
    int total_non_vowels = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the string: ");
        str = (char *)malloc(1000 * sizeof(char)); 
        fgets(str, 1000, stdin); 
        string_length = strlen(str) - 1; 
        str[string_length] = '\0'; 

        if (string_length % size != 0) {
            printf("Error: The string length is not divisible by the number of processes.\n");
            MPI_Finalize();
            return -1;
        }

        non_vowel_counts = (int *)malloc(size * sizeof(int)); 
    }


    MPI_Bcast(&string_length, 1, MPI_INT, 0, MPI_COMM_WORLD);


    int portion_size = string_length / size;


    char *portion = (char *)malloc((portion_size + 1) * sizeof(char)); // +1 for null-terminator


    MPI_Scatter(str, portion_size, MPI_CHAR, portion, portion_size, MPI_CHAR, 0, MPI_COMM_WORLD);


    int non_vowels_in_portion = count_non_vowels(portion, portion_size);


    MPI_Gather(&non_vowels_in_portion, 1, MPI_INT, non_vowel_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);


    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            printf("Process %d found %d non-vowels.\n", i, non_vowel_counts[i]);
        }

        for (int i = 0; i < size; i++) {
            total_non_vowels += non_vowel_counts[i];
        }

        printf("Total number of non-vowels in the string: %d\n", total_non_vowels);
    }

    free(portion);
    if (rank == 0) {
        free(str);
        free(non_vowel_counts);
    }

    MPI_Finalize();
    return 0;
}

