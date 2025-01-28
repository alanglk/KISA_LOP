#include "GA/crossover.hpp"
#include "memory.hpp"
#include "GA/mutation.hpp"

#include <iostream>
#include <memory>
#include <stdio.h>

/**
 * Operadores de Cruce (crossover operators)
 *  */

/// @brief Order crossover operator
/// @param parent1 The first parent to realize the operation
/// @param parent2 The second parent to generate the child
/// @param child Child generated from both parents
/// @param n Number of elements
void cruce_orden(solution_t *parent1, solution_t *parent2, solution_t *child, int n){
    int i, j, z;
    int start, end;

    // Initialize child permutation and matrix
    for (i = 0; i < n; i++){
        child->permutation[i] = -1; // Initialize permutation with -1 value on all positions
        for(j=0; j<n; j++)
            child->matrix[i*n+j] = parent1->matrix[i*n+j]; // Initialize matrix with parent1 values (then execute swaps)
    }

    // Take a random range to maintain from the first parent
    start = rand() % n;
    end = start + rand() % (n - start);

    // Copy the range on the child
    for(i=start; i<=end; i++)
        child->permutation[i] = parent1->permutation[i];

    // Fill the rest with values from parent2 in order
    int exists = 0;
    int next_index = (end+1) % n;
    for(i = 0; i<n; i++){ // loop parent2 elements
        int elem = parent2->permutation[(end+1+i)%n];
        exists = 0;

        // Check if the element is already on the child
        for(j=0; j<n; j++)
            if(child->permutation[j]==elem)
                exists = 1;

        // If the element does not exist on child, insert on the next position
        if(exists == 0){
            child->permutation[next_index] = elem;
            next_index = (next_index + 1) % n;
        }
    }

    // Generate parent1 copy
    solution_t parent1_copy;
    reserve_memory_for_solution(&parent1_copy, n);

    // Generate the child matrix running swap operations on parent1
    // Copy parent 1
    copy_solution(&parent1_copy, parent1, n);

    // Swap matrix on child finding differences from parent1
    for(i=0; i<n; i++)
        // if there is a difference between parent and child swap
        if(parent1_copy.permutation[(end + 1 + i) % n] != child->permutation[(end + 1 + i) % n]) // find the value of the child on parent and swap
            for(j=0; j<n; j++)
                if(parent1_copy.permutation[j] == child->permutation[(end+1+i)%n]){
                    //printf("Difference founded on parent (%d) and child (%d)\n", j, (end+i+1)%n);
                    swap_op(&parent1_copy, n, j, (end+1+i)%n);
                    swap_matrix(child, n, j, (end+1+i)%n);
                }

    free(parent1_copy.matrix);
    free(parent1_copy.permutation);
}

void cruce_mapped(){

}

void cruce_ciclos(){

}
