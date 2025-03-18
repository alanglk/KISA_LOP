#include "GA/GA.hpp"
#include "GA/mutation.hpp"
#include "GA/crossover.hpp"
#include "GA/parent_selection.hpp"
#include "GA/population_selection.hpp"
#include "memory.hpp"

#include <iostream>
#include <memory>
#include <stdio.h>
#include<unistd.h>

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
void GA(population_t *population, int n, int n_population, int steps, int k, float crossover_rate, float mutation_rate, int *evaluations, int *iterations, int *p_best, int *p_worst, int *best_permutation, int *best_value, int criterion, int criterion_value){ // pasar operadores de cruce y mutación?
    // Algorithm loop
    int step = 0;

    int max, min;

    int i, j;
    int n_parents = 2; // two parents to generate a child

    // List to store selected parents indexes from population
    int *i_parents = (int *)malloc(n_parents * sizeof(int));

    int t_criterion = 0;

    // Reserve memory for the new population (child)
    population_t child_population;
    reserve_memory_for_population(&child_population, n, n_population);


    // Evaluate all solutions
    for(i = 0; i<n_population; i++)
    {
        LOP_objective_function(&(population->population[i]), n);
        if(population->population[i].obj_func_value > (*best_value)) 
            (*best_value) = population->population[i].obj_func_value;
        (*evaluations) += 1;
    }

    // find best and worst individuals
    max = -1, min = 9999999;
    for(i = 0; i<n_population; i++){
        if(population->population[i].obj_func_value > max)
            max = population->population[i].obj_func_value;
        if(population->population[i].obj_func_value < min)
            min = population->population[i].obj_func_value;
    }

    p_best[0] = max;
    p_worst[0] = min;

    printf("GA started\n");

    for(step=1; step<steps; step++){

        // Generate the new population by crossover and mutation operations
        i = 0;

        //for(i=0; i<n_population; i++){
        while(i < n_population){
            // Loop until valid child is generated (must be different from other children and actual population members)

            // No parents selected yet for this step
            for(j = 0; j<n_parents; j++)
                i_parents[j] = -1; 

            // Select n_parents to be the parents of the next generation
            tournament(i_parents, n_parents, population, k, n);

            int equals = 1; // 1 for equals

            while(equals == 1){
                equals = 0; // suppose not equals 

                // Take a random range to maintain from the first parent
                int start = rand() % n;
                if(start == (n-1)) start -= 2;

                int end = start + (rand() % n);
                if(end >= n) end = n-1;

                if(start == end){
                    if(start == 0) end+=1;
                    else if(end == n-1) start -= 1;
                    else start -= 1;
                }

                // Crossover operation to generate a child from parents
                if((rand() / RAND_MAX) < crossover_rate){
                    order_crossover(&(population->population[i_parents[0]]), &(population->population[i_parents[1]]), &(child_population.population[i]), n, start, end);
                    order_crossover(&(population->population[i_parents[1]]), &(population->population[i_parents[0]]), &(child_population.population[i+1]), n, start, end);
                }else{
                    copy_solution(&(child_population.population[i]), &(population->population[i_parents[0]]), n);
                    copy_solution(&(child_population.population[i+1]), &(population->population[i_parents[0]]), n);
                }

                
                // Mutation to the child
                int s1, s2;

                // if indexes to swap are the same make a small change
                int n_swaps=1;
                if((rand() / RAND_MAX) < mutation_rate){
                    for(j = 0; j<n_swaps; j++){
                        s1 = rand() % n;
                        s2 = rand() % n;
                        swap_op(&(child_population.population[i]), n, s1, s2);
                        swap_op(&(child_population.population[i+1]), n, s1, s2);
                    }
                }

                j=0;
                while(j<n_population && equals==0){
                    equals = check_equals(&(child_population.population[i]), &(population->population[j]), n);
                    j++;
                }

                j=0;
                while(j<i && equals==0){
                    equals = check_equals(&(child_population.population[i]), &(child_population.population[j]), n);
                    j++;
                }

                j=0;
                while(j<n_population && equals==0){
                    equals = check_equals(&(child_population.population[i+1]), &(population->population[j]), n);
                    j++;
                }

                j=0;
                while(j<i && equals==0){
                    equals = check_equals(&(child_population.population[i+1]), &(child_population.population[j]), n);
                    j++;
                }

                
                if(equals == 0) 
                    equals = check_equals(&(child_population.population[i]), &(child_population.population[i+1]), n);
            }
            i+=2;
        }

        // Evaluate generated solutions
        for(i=0; i<n_population; i++){
            LOP_objective_function(&(child_population.population[i]), n);
            (*evaluations)+=1;
        }
        // Select the population for the next generation        
        elitist_selection(population, &child_population, n, n_population);
        //for(i=0; i<n_population; i++)
        //    copy_solution(&(population->population[i]), &(child_population.population[i]), n);        

        (*iterations) += 1;

        max = -1, min = 99999999;
        for(i = 0; i<n_population; i++){
            if(population->population[i].obj_func_value > max){
                max = population->population[i].obj_func_value;
            }
            if(population->population[i].obj_func_value < min){
                min = population->population[i].obj_func_value;
            }
        }

        // find best and worst individuals
        p_best[step] = max;
        p_worst[step] = min;

        if(max > (*best_value)){
            (*best_value) = max;
            if(criterion == 1)
                t_criterion = 0;
        }
        else{
            if(criterion == 1)
                t_criterion +=1;
        }
        
        if(criterion == 1  && t_criterion >= criterion_value) 
            step = steps; // finish

        if(criterion == 2){
            if((*evaluations) >= criterion_value)
                step = steps;
        }

        /*if(step % 1 == 0){
            printf("Solutions in step %d: max = %d, min = %d\n", step, max, min);
            printf("\n");
        }*/
    }
}
