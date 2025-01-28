#include "include/GA/GA.hpp"


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
            // Make changes
            for(j=0; j<(n*125); j++){
                index1 = rand() % n;
                index2 = rand() % n;
                swap_op(&(population->population[i]), n, index1, index2);
            }

            // if the generated new solution is equal to the original one, repeat the process
            equals = check_equals(&(population->population[i]), init_solution, n);
        }
    }
}


/**
 * GENETIC ALGORITHM CODE
 *  */
void GA(population_t *population, int n, int n_population){ // pasar operadores de cruce y mutación?
    // Algorithm loop
    
    int steps = 10000;
    int step = 0;

    int n_parents = 2; // two parents to generate a child
    int n_generated_childs = 0;
    int i, j, k;

    int *i_parents = (int *)malloc(n_parents * sizeof(int));
    k = 3;

    // n_population must be higher than k

    // Move the next to function???
    population_t child_population;
    reserve_memory_for_population(&child_population, n, n_population);

    printf("Starting GA execution\n");
    for(step=0; step<steps; step++){
        //initialize i_parents
        for(i = 0; i<n_parents; i++)
            i_parents[i] = -1; // no parent selected

        // Select n_parents parents
        tournament(i_parents, n_parents, population, k, n);
        //printf("Tournament passed\n");

        // Generate the new population by crossover and mutation operations
        for(i=0; i<n_population; i++){
            cruce_orden(&(population->population[i_parents[0]]), &(population->population[i_parents[1]]), &(child_population.population[i]), n);
            //printf("%d cruce passed\n", i);
            
            int s1, s2;
            s1 = rand() % n;
            s2 = rand() % n;
            swap_op(&(child_population.population[i]), i, s1, s2);
            //printf("%d swap passed\n", i);
        }
        
        // Compute objective function values
        for(i = 0; i<n_population; i++){
            //if(population->population[i].obj_func_computed==0)
            LOP_objective_function(&(population->population[i]), n);

            //if(child_population.population[i].obj_func_computed==0)
            LOP_objective_function(&(child_population.population[i]), n);
        }

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

        // Selection of the new population
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
        /*if(step % 10 == 0){
            printf("Solutions in step %d: ", step);
            for(i = 0; i<n_population; i++)
                printf("%d ", population->population[i].obj_func_value);
            printf("\n");
        }*/
    }
}
