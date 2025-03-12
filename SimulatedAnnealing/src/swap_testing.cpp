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

    expected_sol->permutation[0] = 1;
    expected_sol->permutation[1] = 0;

    swap_op(sol, 0, 1);

    // Check that the result is equal to the expected solution
    int result = 1; // correct

    // First test
    for(int i=0; i< sol->n; i++)
        if(sol->permutation[i] != expected_sol->permutation[i]){
            result = 0;
        for(int j = 0; j<sol->n; j++){
            if(sol->matrix[i*sol->n+j] != expected_sol->matrix[i*sol->n+j])
                result = 0;
        }
    }

    if(result == 1)
        std::cout << "Test %d on swap operation gone well!\n" << n_test;
    else
    {
        std::cout <<"Test one on swap operation gone wrong! Printing results...\n" << n_test;
        std::cout << "Swap Solution:\n" << *sol << std::endl;
        std::cout << "Expected Solution:\n" << *expected_sol << std::endl;
    }

    return 0;
}

int main(int argc, char *argv[]){
    // run tests
    test(0, argv[1], argv[2]);
    test(1, argv[1], argv[3]);

    return 0;
}