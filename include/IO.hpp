#ifndef IO_HPP
#define IO_HPP

#include "include/LOP.hpp"
#include "include/memory.hpp"

/// @brief Read file and load it into a solution_t struct
/// @param file_name File to read
/// @param sol Struct to store permutation and matrix
/// @return 0 if all gone well, otherwise 1
int read_file(const char *file_name, solution_t *sol, int *n);

/// @brief Print matrix
/// @param n Number of rows and columns
/// @param matrix Matrix to print
void print_matrix(int n, int *matrix);


/// @brief Print array
/// @param array Array to print
/// @param n Number of elements of the array
void print_array(int *array, int n);


/// @brief Print solution permutation and matrix
/// @param solution Solution to print
/// @param n Number of elements
void print_solution(solution_t *solution, int n);

/// @brief Print results on objective function of each solution in the population
/// @param population Population to print results
/// @param n_population Number of solutions on population
void print_results(population_t *population, int n_population, int step);

#endif
