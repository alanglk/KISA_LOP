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
    int n, n_population, steps, evaluations = 0, iterations = 0;

    // randomize seed
    //srand (time(NULL));
    srand(time(NULL));

    solution_t sol;
    population_t population;
    
    // read file and load initial solution
    read_file(argv[1], &sol, &n);

    n_population = strtoul(argv[2], NULL, 10);
    steps = strtoul(argv[3], NULL, 10);
    int k = strtoul(argv[4], NULL, 10);
    float crossover_rate = atof(argv[5]);
    float mutation_rate = atof(argv[6]);

    int criterion = strtoul(argv[8], NULL, 10);
    int criterion_value = strtoul(argv[9], NULL, 10);

    int *best_permutation = (int *)malloc(n * sizeof(int));
    int best_value = 0;

    /*
    criterion 1: until convergence, value: number of iterations withouth improvement
    criterion 2: 
    */
    int *population_worst_list = (int *)malloc(steps * sizeof(int));
    int *population_best_list = (int *)malloc(steps * sizeof(int));

    printf("n: %d, n_population: %d and steps: %d\n\n", n, n_population, steps);

    // Generate new solutions for the population
    printf("Generating new solutions for the initial population\n");
    reserve_memory_for_population(&population, n, n_population);
    generate_new_instance(&population, &sol, sol.n, n_population);

    auto begin = std::chrono::high_resolution_clock::now();    
    // run genetic algorithm
    GA(&population, n, n_population, steps, k, crossover_rate, mutation_rate, &evaluations, &iterations, population_best_list, population_worst_list, best_permutation, &best_value, criterion, criterion_value);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);


    /*int best_index, best_value;
    best_value = -1;

    for(int i=0; i<n_population; i++){
        if(best_value < population.population[i].obj_func_value){
            best_value = population.population[i].obj_func_value;
            best_index = i;
        }
    }*/

    // print best individual
    printf("Best obj. value %d\n", best_value);
    /*for(int j=0; j<n; j++){
        printf("%d ", population.population[best_index].permutation[j]);
    }
    printf("\n");
*/
    printf("Execution informations:\n");
    printf(" - Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    printf(" - Iterations / poblations: %d\n", iterations);
    printf(" - Objective function evaluations: %d\n", evaluations);  

    FILE *output_f = fopen(argv[7], "w");

    for(int i=0; i<iterations;i++)
        fprintf(output_f,"%d ",population_best_list[i]);

    fprintf(output_f, "\n");
    for(int i=0; i<iterations;i++)
        fprintf(output_f,"%d ",population_worst_list[i]);
    fprintf(output_f, "\n");

    // print best permutation founded
    /*for(int i = 0; i<n; i++)
        fprintf(output_f, "%d ", population.population[best_index].permutation[i]);
    fprintf(output_f, "\n");
*/
    fprintf(output_f, "%d ", best_value);
    fprintf(output_f, "\n");

    fprintf(output_f, "%.3f ", elapsed.count() * 1e-9);
    fprintf(output_f, "\n");
    fprintf(output_f, "%d ", iterations);
    fprintf(output_f, "\n");
    fprintf(output_f, "%d\n", evaluations);
    fclose(output_f);

    return 0;
}