#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "LOP.hpp"
#include "IO.hpp"

/// @brief Reserve memory for each solution
/// @param solution Solution pointer to reserve memory
/// @param n Number of elements
void reserve_memory_for_solution(solution_t *solution, int n);

/// @brief Reserve memory for populations
/// @param population Population pointer to reserve memory
/// @param n Number of elements for each solution
/// @param n_population Number of solutions on each population
void reserve_memory_for_population(population_t *population, int n, int n_population);


#endif