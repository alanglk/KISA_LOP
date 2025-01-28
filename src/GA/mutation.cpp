#include "GA/mutation.hpp"

#include <iostream>
#include <memory>
#include <stdio.h>

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