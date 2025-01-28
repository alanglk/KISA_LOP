#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <chrono>

#include "GA/GA.hpp"
#include "memory.hpp"
#include "LOP.hpp"
#include "IO.hpp"


/**
 * K must be lower than n_population, as the amount of competitors selected from population can not be bigger than the actual
 * amount of memebers on that population, it is impossible to find enough competitors
 * 
 * Being n the amount of elements in a permutation, there are !n possible combinations, so population size must be lower than that
 */

int main(int argc, char *argv[]){

    int *solution = NULL, *matrix = NULL; // solution es la permutación que le corresponde a la solución, matrix su matriz
    int n; // cantidad de filas y columnas de la matriz
    int n_population = 5;

    solution_t sol;
    population_t population;

    // read file and load initial solution
    read_file(argv[1], &sol, &n);
    printf("n: %d\n\n", n);

    // Generate new solutions for the population
    printf("Generating new solutions for the initial population\n");
    reserve_memory_for_population(&population, n, n_population);
    generate_new_instance(&population, &sol, sol.n, n_population);

    auto begin = std::chrono::high_resolution_clock::now();    
    GA(&population, n, n_population);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Print population\n");
    for(int i = 0; i<n_population; i++){
        printf("Solution %d, obj. value %d, permutation: ", i, population.population[i].obj_func_value);
        for(int j=0; j<n; j++){
            printf("%d ", population.population[i].permutation[j]);
        }
        printf("\n");
    }
    printf("\n\n");

    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}