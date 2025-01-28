#ifndef GA_HP
#define GA_HPP

#include "LOP.hpp"

/// @brief Generates a population by generating new instances from the actual instance
/// @param population Population of solutions to store generated solutions
/// @param init_solution Initial solution to generate the new ones
/// @param n Number of elements
/// @param n_population Number of elements for the population
void generate_new_instance(population_t *population, solution_t *init_solution, int n, int n_population);

/**
 * GENETIC ALGORITHM CODE
 *  */
void GA(population_t *population, int n, int n_population);

#endif
