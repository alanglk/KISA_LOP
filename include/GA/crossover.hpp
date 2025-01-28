#ifndef CROSSOVER_HPP
#define CROSSOVER_HPP

#include "include/LOP.hpp"

/**
 * Operadores de Cruce (crossover operators)
 *  */

/// @brief Order crossover operator
/// @param parent1 The first parent to realize the operation
/// @param parent2 The second parent to generate the child
/// @param child Child generated from both parents
/// @param n Number of elements
void cruce_orden(solution_t *parent1, solution_t *parent2, solution_t *child, int n);

void cruce_mapped();

void cruce_ciclos();

#endif