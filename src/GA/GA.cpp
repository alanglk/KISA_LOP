#include "GA/GA.hpp"
#include "GA/mutation.hpp"
#include "GA/crossover.hpp"
#include "GA/parent_selection.hpp"
#include "GA/population_selection.hpp"
#include "memory.hpp"

#include <iostream>
#include <memory>
#include <stdio.h>

/// @brief Generates a new instance from the actual instance
/// @param population Population of solutions to store generated solutions
/// @param init_solution Initial solution to generate the new ones
/// @param n Number of elements
/// @param n_population Number of elements for the population
void generate_new_instance(population_t *population, solution_t *init_solution, int n, int n_population){
    population->n_population = n_population;
    population->n = n;

    // Copy the solution readed from file into population
    population->population[0] = *init_solution; // Copy struct values

    // Generate new solutions
    int index1, index2, i, j;
    for(i=1; i<n_population; i++){        
        // Generate new solution by first copying actual and then making changes (n*10 swaps)
        copy_solution(&(population->population[i]), init_solution, n); // copy actual solution
        
        int equals = 1;
        // Loop if new solution is equal to the initial one
        while(equals == 1){
            equals = 0;

            // Make changes
            for(j=0; j<(n*125); j++){
                index1 = rand() % n;
                index2 = rand() % n;
                swap_op(&(population->population[i]), n, index1, index2);
            }

            // if the generated new solution is equal to one already generated, generate another one
            j=0;
            while(j<i && equals == 0){
                equals = check_equals(&(population->population[i]), &(population->population[j]), n);
                j++;
            }
        }
    }
}


/**
 * GENETIC ALGORITHM CODE
 *  */
void GA(population_t *population, int n, int n_population){ // pasar operadores de cruce y mutación?
    // Algorithm loop
    int steps = 100000;
    int step = 0;

    int i, j, k;
    int n_parents = 2; // two parents to generate a child
    k = 50;

    // List to store selected parents indexes from population
    int *i_parents = (int *)malloc(n_parents * sizeof(int));

    // Reserve memory for the new population (child)
    population_t child_population;
    reserve_memory_for_population(&child_population, n, n_population);

    // Evaluate all solutions
    for(i = 0; i<n_population; i++)
        LOP_objective_function(&(population->population[i]), n);

    printf("Starting GA execution\n");
    for(step=0; step<steps; step++){

        // No parents selected yet for this step
        for(i = 0; i<n_parents; i++)
            i_parents[i] = -1; 

        // Select n_parents to be the parents of the next generation
        tournament(i_parents, n_parents, population, k, n);
        //printf("TOurnament finished\n");

        // Generate the new population by crossover and mutation operations
        for(i=0; i<n_population; i++){
            // Loop until valid child is generated (must be different from other children and actual population members)
            int equals = 1; // 1 for equals

            while(equals == 1){
                equals = 0; // suppose not equals 

                // Take a random range to maintain from the first parent
                int start = rand() % n;
                int end = start + rand() % (n - start);
                
                // Crossover operation to generate a child from parents
                order_crossover(&(population->population[i_parents[0]]), &(population->population[i_parents[1]]), &(child_population.population[i]), n, start, end);
                //printf("Order finisged\n");
                // Mutation to the child
                int s1, s2;

                // if indexes to swap are the same make a small change
                int n_swaps = rand() % (n/4);
                //n_swaps += (n/4);
                for(j = 0; j<n_swaps; j++){
                    s1 = rand() % n;
                    s2 = rand() % n;
                    swap_op(&(child_population.population[i]), n, s1, s2);
                }
                //printf("Swap finished\n");

                // Check that generated child is different from other children and actual population members
                j=0;
                while(j<n_population && equals==0){
                    equals = check_equals(&(child_population.population[i]), &(population->population[j]), n);
                    j++;
                }
                //for(j = 0; j<n_population; j++)

                j=0;
                while(j<i && equals==0){
                    equals = check_equals(&(child_population.population[i]), &(child_population.population[j]), n);
                    j++;
                }
                //for(j = 0; j<i; j++)
                //    equals = check_equals(&(child_population.population[i]), &(child_population.population[j]), n);

                // If a member is equal to new child, the next iteration of the while will be executed generating another child
            }

            // Evaluate the new VALID solution
            LOP_objective_function(&(child_population.population[i]), n);
        }

        //printf("in elitism\n");
        /*print_results(population, n_population, step);

        printf("=================\n=================\n");
        printf("Print population\n");
        for(i = 0; i<n_population; i++){
            printf("Solution %d, obj. value %d, permutation: ", i, population->population[i].obj_func_value);
            for(j=0; j<n; j++){
                printf("%d ", population->population[i].permutation[j]);
            }
            printf("\n");
        }*/

        /*for(i = 0; i<n_population; i++){
            print_matrix(n, population->population[i].matrix);
        }*/

        /*printf("\n\n");
        
        printf("Print child population\n");
        for(i = 0; i<n_population; i++){
            printf("Solution %d, obj. value %d, permutation: ", i, child_population.population[i].obj_func_value);
            for(j=0; j<n; j++){
                printf("%d ", child_population.population[i].permutation[j]);
            }
            printf("\n");
        }
        //printf("\n\n");*/


        // Select the population for the next generation
        elitist_selection(population, &child_population, n, n_population);
        
        
        //printf("Elitism passed\n");
        // Not really necessary
        /*for(i = 0; i<n_population; i++){
            if(population->population[i].obj_func_computed==0)
                LOP_objective_function(&(population->population[i]), n);
        }*/

        /*printf("=================\n");

        
        printf("Print population\n");
        for(i = 0; i<n_population; i++){
            printf("Solution %d, obj. value %d, permutation: ", i, population->population[i].obj_func_value);
            for(j=0; j<n; j++){
                printf("%d ", population->population[i].permutation[j]);
            }
            printf("\n");
        }
        printf("\n\n");
        
        printf("Print child population\n");
        for(i = 0; i<n_population; i++){
            printf("Solution %d, obj. value %d, permutation: ", i, child_population.population[i].obj_func_value);
            for(j=0; j<n; j++){
                printf("%d ", child_population.population[i].permutation[j]);
            }
            printf("\n");
        }
        printf("\n\n");

        printf("=================\n=================\n");*/
        if(step % 100 == 0){
            printf("Solutions in step %d: \n", step);
            for(i = 0; i<n_population; i++){
                printf("Obj.value = %d, permutation: ", population->population[i].obj_func_value);
                for(j=0; j<15; j++){
                    printf("%d ", population->population[i].permutation[j]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}
