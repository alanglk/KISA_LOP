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
/// @param start Start index to maintain from parent1
/// @param end End index to maitain from parent1
void order_crossover(solution_t *parent1, solution_t *parent2, solution_t *child, int n, int start, int end){
    int i, j;

//    printf("In order crossover, %d, %d\n", start, end);

    // Initialize child permutation and matrix with parent 1 values
    for (i = 0; i < n; i++){
        child->permutation[i] = parent1->permutation[i]; // Initialize permutation with -1 value on all positions
        for(j=0; j<n; j++)
            child->matrix[i*n+j] = parent1->matrix[i*n+j]; // Initialize matrix with parent1 values (then execute swaps)
    }


    /*if(end<start){
        for(i=start; i<n; i++)
            child->permutation[i] = parent1->permutation[i];
        for(i=0; i<=end; i++)
            child->permutation[i] = parent1->permutation[i];
    }*/

    // Fill the rest with values from parent2 in order
    int exists = 0;
    int next_index = (end+1) % n; // end is the last index of the copied part
    for(i = 0; i<n; i++){ // loop parent2 elements
        int elem = parent2->permutation[(end+1+i)%n];
        exists = 0;

        // Check if the element is already on the child
        for(j=0; j<(end+i-start+1); j++)
            if(child->permutation[(j+start) % n]==elem)
                exists = 1;

        // If the element does not exist on child, insert on the next position
        if(exists == 0){
            child->permutation[next_index] = elem;
            next_index = (next_index + 1) % n;
        }
    }

    // Now make the necessary swaps on matrix of child, using parent1 copy to know what swaps must be done
    // Generate parent1 copy
    solution_t parent1_copy;
    reserve_memory_for_solution(&parent1_copy, n);
    copy_solution(&parent1_copy, parent1, n);

    // Swap matrix on child finding differences from parent1
    for(i=0; i<n; i++) {
        // if there is a difference between parent and child swap
        if(parent1_copy.permutation[(end + 1 + i) % n] != child->permutation[(end + 1 + i) % n]) { // find the value of the child on parent and swap
            for(j=0; j<n; j++){
                if(parent1_copy.permutation[j] == child->permutation[(end+1+i)%n]){
                    //swap_op(&parent1_copy, n, j, (end+1+i)%n);
                    //swap_permutation(child, n, j, (end+1+i)%n);

                    swap_matrix(child, n, j, (end+1+i)%n);
                }
            }
        }
    }

    // free memory occuped by parent1 copy
    free(parent1_copy.matrix);
    free(parent1_copy.permutation);
}

void cruce_mapped(){

}

void cruce_ciclos(){

}
