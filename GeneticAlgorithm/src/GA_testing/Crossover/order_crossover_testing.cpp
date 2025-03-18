#include "IO.hpp"
#include "memory.hpp"
#include "LOP.hpp"
#include "GA/mutation.hpp"
#include "GA/crossover.hpp"

#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <chrono>

int test(int n_test, const char *file1, const char *file2, const char *file3){
    printf("Running test %d for operator ORDER CROSSOVER...\n", n_test);

    int n; // cantidad de filas y columnas de la matriz
    solution_t parent1, parent2, child, expected_child;

    // read initial solution and expected solution
    read_file(file1, &parent1, &n);
    read_file(file2, &parent2, &n);
    read_file(file3, &expected_child, &n);

    // Reserve memory for child
    reserve_memory_for_solution(&child, n);

    // Indexes for order crossover
    int start=1, end=2; // both included

    // Run the function to test
    order_crossover(&parent1, &parent2, &child, n, start, end);

    // Check that the result is equal to the expected solution
    int result = 1; // correct

    // First test
    for(int i=0; i<n; i++)
        if(child.permutation[i] != expected_child.permutation[i]){
            result = 0;
        for(int j = 0; j<n; j++){
            if(child.matrix[i*n+j] != expected_child.matrix[i*n+j])
                result = 0;
        }
    }

    if(result == 1)
        printf("Test %d on ORDER CROSSOVER gone well!\n", n_test);
    else
    {
        printf("Test one on ORDER CROSSOVER gone wrong! Printing results...\n", n_test);
        print_solution(&child, n);
        print_solution(&expected_child, n);
    }

    return 0;
}

int main(int argc, char *argv[]){
    // Run tests
    int n_test = strtoul(argv[1], NULL, 10);
    test(n_test, argv[2], argv[3], argv[4]);

    return 0;
}