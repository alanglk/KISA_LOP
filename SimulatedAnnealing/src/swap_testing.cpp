#include <iostream>
#include <string>
#include <memory>
#include "LOP.hpp"

using namespace std;

int test(int n_test, string file1, string file2){
    printf("Ejecutando tests del operador swap...\n");
    
    auto sol = std::make_unique<solution_t>();
    auto expected_sol = std::make_unique<solution_t>();

    // read initial solution and expected solution
    read_from_file(file1, sol);
    read_from_file(file2, expected_sol);

    std::cout << "Initial state:\n" << *sol << std::endl << std::endl;

    swap_op(sol, 1, 3);
    LOP_objective_function(sol); // Recalculate the Objective Function
    expected_sol->permutation = {0, 3, 2, 1};

    // Check that the result is equal to the expected solution
    bool result = true; // correct

    // First test
    for(int i=0; i< sol->n; i++)
        if(sol->permutation[i] != expected_sol->permutation[i]){
            result = false;
        for(int j = 0; j<sol->n; j++){
            if(sol->matrix[i*sol->n+j] != expected_sol->matrix[i*sol->n+j])
                result = false;
        }
    }
    result = result & ( sol->obj_func_value == expected_sol->obj_func_value );

    if(result)
        std::cout << "Test " << n_test << " on swap operation gone well!\n" << n_test;
    else
        std::cout <<"Test one on swap operation gone wrong! Printing results...\n" << n_test;
    
    std::cout << "Swap Solution:\n" << *sol << std::endl;
    std::cout << "Expected Solution:\n" << *expected_sol << std::endl;

    return 0;
}

int main(int argc, char *argv[]){
    // run tests
    test(0, argv[1], argv[2]);

    return 0;
}