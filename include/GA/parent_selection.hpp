#ifndef PARENT_SELECTION_HPP
#define PARENT_SELECTION_HPP

#include "include/LOP.hpp"

/**
 * Selection functions
 */

void ruleta();

void elitista();

/// @brief Tournament to select the parents of the new generation
/// @param selected_parents Indexes of solutions selected as parents
/// @param n_parents Number of parents of the new generation
/// @param population Population of solutions
/// @param k Number of solutions that compite on the tournament to be the parent
/// @param n Number of elements
void tournament(int *selected_parents, int n_parents, population_t *population, int k, int n);


#endif