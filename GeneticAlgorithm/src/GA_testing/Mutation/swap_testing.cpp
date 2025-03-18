#include "IO.hpp"
#include "memory.hpp"
#include "LOP.hpp"
#include "GA/mutation.hpp"

#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <chrono>

int test(int n_test, char *file1, char *file2){
    printf("Ejecutando tests del operador swap...\n");
    
    int *solution = NULL, *matrix = NULL; // solution es la permutación que le corresponde a la solución, matrix su matriz
    int n; // cantidad de filas y columnas de la matriz

    // define solution
    solution_t sol, expected_sol;

    // read initial solution and expected solution
    read_file(file1, &sol, &n);
    read_file(file2, &expected_sol, &n);
    expected_sol.permutation[0]  = 1;
    expected_sol.permutation[1] = 0;

    swap_op(&sol, n, 0, 1);

    // Check that the result is equal to the expected solution
    int result = 1; // correct

    // First test
    for(int i=0; i<n; i++)
        if(sol.permutation[i] != expected_sol.permutation[i]){
            result = 0;
        for(int j = 0; j<n; j++){
            if(sol.matrix[i*n+j] != expected_sol.matrix[i*n+j])
                result = 0;
        }
    }

    if(result == 1)
        printf("Test %d on swap operation gone well!\n", n_test);
    else
    {
        printf("Test one on swap operation gone wrong! Printing results...\n", n_test);
        print_solution(&sol, n);
        print_solution(&expected_sol, n);
    }

    return 0;
}

int main(int argc, char *argv[]){
    // run tests
    test(0, argv[1], argv[2]);
    test(1, argv[1], argv[3]);

    return 0;
}