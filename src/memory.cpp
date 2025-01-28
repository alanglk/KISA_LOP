#include "../include/memory.hpp"

/// @brief Reserve memory for each solution
/// @param solution Solution pointer to reserve memory
/// @param n Number of elements
void reserve_memory_for_solution(solution_t *solution, int n){
    solution->n = n;
    solution->matrix = (int *)malloc(n * n * sizeof(int));
    solution->permutation = (int *)malloc(n * sizeof(int));

    solution->obj_func_value = 0;
    solution->obj_func_computed = 0;
}


/// @brief Reserve memory for populations
/// @param population Population pointer to reserve memory
/// @param n Number of elements for each solution
/// @param n_population Number of solutions on each population
void reserve_memory_for_population(population_t *population, int n, int n_population){
    population->n = n;
    population->n_population = n_population;
    population->population = (solution_t *)malloc(n_population * sizeof(solution_t));

    for(int i = 0; i < n_population; i++)
        reserve_memory_for_solution(&(population->population[i]), n);
}