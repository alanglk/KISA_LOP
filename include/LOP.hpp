#ifndef LOP_HPP
#define LOP_HPP

#include <ostream>

typedef struct {
    int *permutation;
    int *matrix;
    int n;
    int obj_func_computed;
    int obj_func_value;
} solution_t;

typedef struct {
    solution_t *population;
    int n;
    int n_population;
} population_t;

typedef struct {
    int obj_value;
    int index;
} solution_result_t;


/// @brief Copies a solution into another one
/// @param solution1 Solution in which to copy the solution
/// @param solution2 Solution to copy in another
/// @param n Number of elements
void copy_solution(solution_t *solution1, solution_t *solution2, int n);

/// @brief Exchange two solutions
/// @param solution1 Solution1 to move to solution2
/// @param solution2 Solution2 to move to solution 1
/// @param n Number of elements
void exchange_solutions(solution_t *solution1, solution_t *solution2, int n);

/// @brief Compare permutations of solutions to evaluate if both solution are equals
/// @param sol1 First solution to compare
/// @param sol2 Second solution to compare
/// @param n Number of elements
/// @return If solutions are equals
int check_equals(solution_t *sol1, solution_t *sol2, int n);

/// @brief Objective function for LOP problem
/// @param sol Structure with information to compute and store the objective function
/// @param n Number of elements
void LOP_objective_function(solution_t *sol, int n);

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

/// @brief sysout overloading
std::ostream& operator<<(std::ostream& out, const solution_t& s);

#endif