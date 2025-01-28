#include "IO.hpp"
#include "memory.hpp"
#include "LOP.hpp"
#include "GA/mutation.hpp"
#include "GA/parent_selection.hpp"
#include "GA/GA.hpp"

#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <chrono>

int test(int n_test, const char *file1, int n_parents, int n_population, int k){
    printf("Running test %d for operator TOURNAMENT PARENT SELECTOR...\n", n_test);

    int n; // cantidad de filas y columnas de la matriz
    population_t population;
    solution_t solution;

    printf("Test configuration:\n - k = %d\n - n_population = %d\n - n_parents = %d\n", k, n_population, n_parents);

    // read initial solution and expected solution
    read_file(file1, &solution, &n);

    // Reserve memory for population
    reserve_memory_for_population(&population, n, n_population);

    // Initialize population
    generate_new_instance(&population, &solution, n, n_population);

    // List to store selected parents indexes
    int *parents = (int *)malloc(n_parents * sizeof(int));

    // Compute objective function value
    for(int i = 0; i<n_population; i++){
        LOP_objective_function(&(population.population[i]), n);
    }

    // Run the function to test
    tournament(parents, n_parents, &population, k, n);

    printf("Test %d for TOURNAMENT SELECTION finished\n", n_test);
}

int main(int argc, char *argv[]){
    // Run tests
    int n_test = strtoul(argv[1], NULL, 10);
    test(n_test, argv[2], 2, 5, 3); // n = 5
    test(n_test+1, argv[3], 2, 5, 3); // n = 10
    test(n_test+2, argv[3], 2, 10, 5); // n = 10
    test(n_test+3, argv[4], 2, 5, 3); // n = 4
    test(n_test+4, argv[4], 2, 5, 4); // n = 4
    test(n_test+4, argv[4], 2, 6, 2); // n = 4
    return 0;
}