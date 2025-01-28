#include "IO.hpp"
#include "memory.hpp"
#include "LOP.hpp"
#include "GA/mutation.hpp"
#include "GA/population_selection.hpp"

#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <chrono>

int test(int n_test, char *file1, char *file2, char *file3, char *file4){
    printf("Running test for operator ELITIST POPULATION SELECTOR...\n");
    
    int n;

    population_t population, child_population;
    solution_t s1, s2, s3, s4;

    solution_t exp_s1, exp_s2;

    read_file(file1, &s1, &n);
    read_file(file2, &s2, &n);
    read_file(file3, &s3, &n);
    read_file(file4, &s4, &n);

    // read again the best two solutions
    read_file(file2, &exp_s1, &n);
    read_file(file3, &exp_s2, &n);

    reserve_memory_for_population(&population, n, 2);
    reserve_memory_for_population(&child_population, n, 2);

    population.population[0] = s1;
    population.population[1] = s2;
    child_population.population[0] = s3;
    child_population.population[1] = s4;

    elitist_selection(&population, &child_population, n, 2);

    // The two on the population must be equals to the two exp
    
    int correct = 0;
    if((check_equals(&(population.population[0]), &exp_s1, n) == 1 || check_equals(&(population.population[0]), &exp_s2, n) == 1) &&
        (check_equals(&(population.population[1]), &exp_s1, n) == 1 || check_equals(&(population.population[1]), &exp_s2, n) == 1))
        correct = 1;

    if(correct==1)
        printf("ELITIS POPULATION SELECTOR WORKS CORRECTLY\n");
    else
        printf("ELITIS POPULATION SELECTOR FAILED\n");

    return 0;
}

int main(int argc, char *argv[]){
    // run tests
    test(0, argv[2], argv[3], argv[4], argv[5]);

    return 0;
}