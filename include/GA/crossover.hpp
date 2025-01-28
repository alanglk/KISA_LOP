#ifndef CROSSOVER_HPP
#define CROSSOVER_HPP

#include "LOP.hpp"

/**
 * Operadores de Cruce (crossover operators)
 *  */


/// @brief Order crossover operator
/// @param parent1 The first parent to realize the operation
/// @param parent2 The second parent to generate the child
/// @param child Child generated from both parents
/// @param n Number of elements
/// @param start Start index to maintain from parent1
/// @param end End index to maitain from parent1
void order_crossover(solution_t *parent1, solution_t *parent2, solution_t *child, int n, int start, int end);

void cruce_mapped();

void cruce_ciclos();

#endif