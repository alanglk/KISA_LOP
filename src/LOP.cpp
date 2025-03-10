#include "LOP.hpp"
#include "memory.hpp"

#include <iostream>
#include <memory>
#include <stdio.h>

/// @brief Copies a solution into another one
/// @param solution1 Solution in which to copy the solution
/// @param solution2 Solution to copy in another
/// @param n Number of elements
void copy_solution(solution_t *solution1, solution_t *solution2, int n){
    for(int i = 0; i<n; i++){
        solution1->permutation[i] = solution2->permutation[i];
        for(int j = 0; j<n; j++)
            solution1->matrix[i*n+j] = solution2->matrix[i*n+j];
    }
    solution1->n = solution2->n;
    solution1->obj_func_computed = solution2->obj_func_computed;
    solution1->obj_func_value = solution2->obj_func_value;
}

/// @brief Exchange two solutions
/// @param solution1 Solution1 to move to solution2
/// @param solution2 Solution2 to move to solution 1
/// @param n Number of elements
void exchange_solutions(solution_t *solution1, solution_t *solution2, int n){
    solution_t temp_solution;
    reserve_memory_for_solution(&temp_solution, n);

    copy_solution(&temp_solution, solution1, n);
    copy_solution(solution1, solution2, n);
    copy_solution(solution2, &temp_solution, n);

    free(temp_solution.matrix);
    free(temp_solution.permutation);
}

/// @brief Compare permutations of solutions to evaluate if both solution are equals
/// @param sol1 First solution to compare
/// @param sol2 Second solution to compare
/// @param n Number of elements
/// @return If solutions are equals
int check_equals(solution_t *sol1, solution_t *sol2, int n){
    for(int i = 0; i<n; i++)
        if(sol1->permutation[i] != sol2->permutation[i])
            return 0; // not equals
    return 1; // equals
}


/// @brief Objective function for LOP problem
/// @param sol Structure with information to compute and store the objective function
/// @param n Number of elements
void LOP_objective_function(solution_t *sol, int n){
    sol->obj_func_value = 0;
    for(int i = 0; i<(n+1)/2; i++)
        for(int j = i+1; j<n; j++)
            sol->obj_func_value += sol->matrix[i*n+j];
    sol->obj_func_computed=1;
}

int factorial(int n){
    if (n <= 0)
        return 1; 
    return n * (factorial(n-1));
}

void evaluate_all_solutions(solution_t *init_sol, int n){

    //copy initial solution n times
    solution_t sol2, sol3, sol4;

    int lower_amount_solution = factorial(n-1);
    int amount_solution = lower_amount_solution * n;
    for(int i = 0; i<n; i++){
        
    }
}


/// @brief Swap values on permutation of solution_t. Cost O(1)
/// @param solution Solution_t structure with the permutation
/// @param n Number of elements
/// @param s1 First index to swap
/// @param s2 Second index to swap
void swap_permutation(solution_t *solution, int n, int s1, int s2){
    // swap permutation | O(1)
    int tmp = solution->permutation[s1];
    solution->permutation[s1] = solution->permutation[s2];
    solution->permutation[s2] = tmp;
}

/// @brief Swap matrix of Solution_t. Cost O(2N) --> O(N)
/// @param solution Solution_t structure with the permutation
/// @param n Number of elements
/// @param s1 First index to swap
/// @param s2 Second index to swap
void swap_matrix(solution_t *solution, int n, int s1, int s2){
    int *temp = (int *)malloc(n * sizeof(int));
    int tmp;

    // swap matrix | twp phases: O(N) + O(N) = O(2N) === O(N)
    // first phase O(n)
    int i;
    for(i=0; i<n; i++){
        temp[i] = solution->matrix[s1 * n + i];
        solution->matrix[s1 * n + i] = solution->matrix[s2 * n + i];
        solution->matrix[s2 * n + i] = temp[i]; // copy the value, no the pointer
    }

    free(temp); // this pointer can be liberated as values have been copied, no the pointer itself

    for(i = 0; i<n; i++){
        tmp = solution->matrix[i * n + s1];
        solution->matrix[i * n + s1] = solution->matrix[i * n + s2];
        solution->matrix[i * n + s2] = tmp; 
    }    
}

/// @brief Swap operation between two elements. Swaps permutation and matrix. Computational cost: O(2N) --> O(N)
/// @param solution Structure with permutation and matrix to swap
/// @param n Number of elements
/// @param s1 First index to swap with
/// @param s2 Second index to swap with
void swap_op(solution_t *solution, int n, int s1, int s2){
    if(s1 == s2) 
        s2 = (s2 + 1) % n; // indexes to swap can not be the same

    // swap the permutation
    swap_permutation(solution, n, s1, s2);
    // swap the matrix
    swap_matrix(solution, n, s1, s2);
}
