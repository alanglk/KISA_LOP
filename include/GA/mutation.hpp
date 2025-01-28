#ifndef MUTATION_HPP
#define MUTATION_HPP

#include "include/LOP.hpp"

/// @brief Swap values on permutation of solution_t. Cost O(1)
/// @param solution Solution_t structure with the permutation
/// @param n Number of elements
/// @param s1 First index to swap
/// @param s2 Second index to swap
void swap_permutation(solution_t *solution, int n, int s1, int s2);

/// @brief Swap matrix of Solution_t. Cost O(2N) --> O(N)
/// @param solution Solution_t structure with the permutation
/// @param n Number of elements
/// @param s1 First index to swap
/// @param s2 Second index to swap
void swap_matrix(solution_t *solution, int n, int s1, int s2);

/// @brief Swap operation between two elements. Swaps permutation and matrix. Computational cost: O(2N) --> O(N)
/// @param solution Structure with permutation and matrix to swap
/// @param n Number of elements
/// @param s1 First index to swap with
/// @param s2 Second index to swap with
void swap_op(solution_t *solution, int n, int s1, int s2);


#endif