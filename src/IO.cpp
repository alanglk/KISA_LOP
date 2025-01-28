#include "IO.hpp"
#include "memory.hpp"

#include <iostream>
#include <memory>
#include <stdio.h>

/// @brief Read file and load it into a solution_t struct
/// @param file_name File to read
/// @param sol Struct to store permutation and matrix
/// @return 0 if all gone well, otherwise 1
int read_file(const char *file_name, solution_t *sol, int *n){
    FILE *f = fopen(file_name, "r");
        if (f == NULL){
        perror("Error opening the file\n");
        return 1;
    } 
    printf("File oppened!\n");

    // read n value
    fscanf(f, "%d", n);

    // reserve memory for the solution
    reserve_memory_for_solution(sol, (*n));

    // read permutation matrix from file and initialize the permutation
    for(int i = 0; i<sol->n; i++){
        sol->permutation[i] = i;
        for(int j= 0; j<sol->n; j++)
            fscanf(f, "%d", &(sol->matrix[i*(*n)+j]));
    }

    return 0;
}

/// @brief Print matrix
/// @param n Number of rows and columns
/// @param matrix Matrix to print
void print_matrix(int n, int *matrix){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++)
            printf("%d ", matrix[i*n+j]);
        printf("\n");
    }
    printf("\n");
}


/// @brief Print array
/// @param array Array to print
/// @param n Number of elements of the array
void print_array(int *array, int n){
    for(int i = 0; i<n; i++)
        printf("%d ", array[i]);
    printf("\n\n");
}


/// @brief Print solution permutation and matrix
/// @param solution Solution to print
/// @param n Number of elements
void print_solution(solution_t *solution, int n){
    printf("============\nPrinting solution.\n");
    print_array(solution->permutation, n);
    print_matrix(n, solution->matrix);
}


/// @brief Print results on objective function of each solution in the population
/// @param population Population to print results
/// @param n_population Number of solutions on population
void print_results(population_t *population, int n_population, int step){
    printf("Results on step %d: ", step);
    for(int i = 0; i<n_population; i++)
        printf("%d, ", population->population[i].obj_func_value);
    printf("\n\n");
}