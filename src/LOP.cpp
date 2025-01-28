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