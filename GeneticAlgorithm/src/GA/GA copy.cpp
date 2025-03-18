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
void GA(population_t *population, int n, int n_population, int steps, int k, float crossover_rate, float mutation_rate, int *evaluations, int *iterations, int *p_best, int *p_worst){ // pasar operadores de cruce y mutación?
    // Algorithm loop
    int step = 0;

    int i, j;
    int n_parents = 2; // two parents to generate a child

    // List to store selected parents indexes from population
    int *i_parents = (int *)malloc(n_parents * sizeof(int));

    // Reserve memory for the new population (child)
    population_t child_population;
    reserve_memory_for_population(&child_population, n, n_population);


    printf("Starting GA\n");
    // Evaluate all solutions
    for(i = 0; i<n_population; i++)
    {
        LOP_objective_function(&(population->population[i]), n);
        (*evaluations) += 1;
    }

    for(step=0; step<steps; step++){

        // find best and worst individuals
        int max = -1, min = 99999999;
        for(i = 0; i<n_population; i++){
            if(population->population[i].obj_func_value > max)
                max = population->population[i].obj_func_value;
            if(population->population[i].obj_func_value < min)
                min = population->population[i].obj_func_value;
        }

        p_best[step] = max;
        p_worst[step] = min;


        // Generate the new population by crossover and mutation operations
        i = 0;

        //for(i=0; i<n_population; i++){
        while(i < n_population){
            // Loop until valid child is generated (must be different from other children and actual population members)

            // No parents selected yet for this step
            for(i = 0; i<n_parents; i++)
            i_parents[i] = -1; 

            // Select n_parents to be the parents of the next generation
            tournament(i_parents, n_parents, population, k, n);


            int equals = 1; // 1 for equals

            

            //printf("Mutation: %d, crossover: %d, p_mut: %f, p_crossover: %f\n", mutate, crossover, mutation_rate, crossover_rate);

            while(equals == 1){
                equals = 0; // suppose not equals 

                // Take a random range to maintain from the first parent
                int start = rand() % n;
                if(start == (n-1)) start -= 2;

                int end = start + (rand() % n);//(start + (rand()%(n))) % (n);// - start);
                if(end >= n) end = n-1;

                if(start == end){
                    if(start == 0) end+=1;
                    else if(end == n-1) start -= 1;
                    else start -= 1;
                }


                //printf("Child %d, Starting crossover 1, start = %d, end = %d\n", i, start, end);
                // Crossover operation to generate a child from parents
                if((rand() / RAND_MAX) < crossover_rate)
                    order_crossover(&(population->population[i_parents[0]]), &(population->population[i_parents[1]]), &(child_population.population[i]), n, start, end);
                else
                    copy_solution(&(child_population.population[i]), &(population->population[i_parents[0]]), n);

                //copy_solution(&(child_population.population[i]), &(population->population[i]), n);
                
                //printf("Crossover done\n");
                /*printf("\n=====\n");
                printf("Start = %d, end = %d\n", start, end);
                printf("Parent1: ");
                for(j = 0; j<n; j++)
                    printf("%d ", population->population[i_parents[0]].permutation[j]);
                printf("\n");
                printf("Parent2: ");
                for(j = 0; j<n; j++)
                    printf("%d ", population->population[i_parents[1]].permutation[j]);
                printf("\n");
                printf("Child: ");
                for(j = 0; j<n; j++)
                    printf("%d ", child_population.population[i].permutation[j]);
                printf("\n");
                printf("\n========\n");
*/

                // Mutation to the child
                int s1, s2;

                // if indexes to swap are the same make a small change
                //int n_swaps = rand() % int(n);
                int n_swaps=1;
                
                if((rand() / RAND_MAX) < mutation_rate)
                    for(j = 0; j<n_swaps; j++){
                        s1 = rand() % n;
                        s2 = rand() % n;
                        swap_op(&(child_population.population[i]), n, s1, s2);
                    }

                //printf("Mutation done\n");
                // Check that generated child is different from other children and actual population members
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

                // If a member is equal to new child, the next iteration of the while will be executed generating another child

                // acept child only if it is better than the worst member of the last population
                //LOP_objective_function(&(child_population.population[i]), n);
                //(*evaluations) += 1;
                
                //if(child_population.population[i].obj_func_value < (min-int(min/8))){
                //    equals = 1;
                    /*printf("Solution not accepted: obj = %d, worst member = %d, permutation: ", child_population.population[i].obj_func_value, worst_member);
                        for(j=0; j<n; j++){
                            printf("%d ", child_population.population[i].permutation[j]);
                        }*/
                    //printf("\n");
                }
            }
            i+=1;

            //equals = 1; // 1 for equals

            //printf("Child1 generated\n");
            while(equals == 1){
                equals = 0; // suppose not equals 

                // Take a random range to maintain from the first parent
                int start = rand() % n;
                if(start == (n-1)) start -= 2;

                int end = start + (rand() % n);//(start + (rand()%(n))) % (n);// - start);
                if(end >= n) end = n-1;

                if(start == end){
                    if(start == 0) end+=1;
                    else if(end == n-1) start -= 1;
                    else start -= 1;
                }

                //printf("Child %d, Starting crossover 2, start = %d, end = %d\n", i, start, end);
                // Crossover operation to generate a child from parents
                if((rand() / RAND_MAX) < crossover_rate)
                    order_crossover(&(population->population[i_parents[1]]), &(population->population[i_parents[0]]), &(child_population.population[i]), n, start, end);
                else
                    copy_solution(&(child_population.population[i]), &(population->population[i_parents[1]]), n);


                //printf("Crossover done\n");
                // Mutation to the child
                int s1, s2;

                // if indexes to swap are the same make a small change
                int n_swaps=1;
                
                if((rand() / RAND_MAX) < mutation_rate)
                    for(j = 0; j<n_swaps; j++){
                        s1 = rand() % n;
                        s2 = rand() % n;
                        swap_op(&(child_population.population[i]), n, s1, s2);
                    }
                
                //printf("mutation done\n");
                // acept child only if it is better than the worst member of the last population
                LOP_objective_function(&(child_population.population[i]), n);
                (*evaluations) += 1;
                
                if(child_population.population[i].obj_func_value < (min-int(min/8)))
                    equals = 1;
            }
            //printf("Child2 generated\n");

            i+=1;
            // Evaluate the new VALID solution
            //LOP_objective_function(&(child_population.population[i]), n);
            //printf("Child %d generated\n", i);
        }

        // Select the population for the next generation        
        //elitist_selection(population, &child_population, n, n_population);
        for(i=0; i<n_population; i++)
            copy_solution(&(population->population[i]), &(child_population.population[i]), n);        
        //random_selection(population, &child_population, n, n_population);

        (*iterations) += 1;
        if(step % 1 == 0){
            int max = -1, min = 99999999;

            for(i = 0; i<n_population; i++){
                if(population->population[i].obj_func_value > max)
                    max = population->population[i].obj_func_value;
                if(population->population[i].obj_func_value < min)
                    min = population->population[i].obj_func_value;
            }
            
            printf("Solutions in step %d: max = %d, min = %d\n", step, max, min);
            /*for(i = 0; i<n_population; i++){
                printf("Obj.value = %d, permutation: ", population->population[i].obj_func_value);
                for(j=0; j<n; j++){
                    printf("%d ", population->population[i].permutation[j]);
                }
                printf("\n");

                for(j=0;j<n;j++){
                    for(int z = 0; z<n; z++){
                        printf("%d ", population->population[i].matrix[j*n+z]);
                    }
                    printf("\n");
                }*/
            //}
            printf("\n");
        }
        //sleep(5);
    }
}
