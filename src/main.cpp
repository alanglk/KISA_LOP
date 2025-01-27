#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <chrono>
#include "include/common.hpp"


typedef struct {
    int *permutation;
    int *matrix;
    int n;
    int obj_func_computed;
    int obj_func_value;
} solution_t;

typedef struct {
    solution_t *population;
    int n;
    int n_population;
} population_t;

typedef struct {
    int obj_value;
    int index;
} solution_result_t;


/// @brief Reserve memory for each solution
/// @param solution Solution pointer to reserve memory
/// @param n Number of elements
void reserve_memory_for_solution(solution_t *solution, int n){
    solution->n = n;
    solution->matrix = (int *)malloc(n * n * sizeof(int));
    solution->permutation = (int *)malloc(n * sizeof(int));

    solution->obj_func_value = 0;
    solution->obj_func_computed = 0;
}


/// @brief Reserve memory for populations
/// @param population Population pointer to reserve memory
/// @param n Number of elements for each solution
/// @param n_population Number of solutions on each population
void reserve_memory_for_population(population_t *population, int n, int n_population){
    population->n = n;
    population->n_population = n_population;
    population->population = (solution_t *)malloc(n_population * sizeof(solution_t));

    for(int i = 0; i < n_population; i++)
        reserve_memory_for_solution(&(population->population[i]), n);
}

void copy_solution(solution_t *solution1, solution_t *solution2, int n){
    for(int i = 0; i<n; i++){
        solution1->permutation[i] = solution2->permutation[i];
        for(int j = 0; j<n; j++)
            solution1->matrix[i*n+j] = solution2->matrix[i*n+j];
    }
    solution1->n = solution2->n;
    solution1->obj_func_computed = solution2->obj_func_computed;
    solution1->obj_func_value = solution2->obj_func_value;
}

void exchange_solutions(solution_t *solution1, solution_t *solution2, int n){
    solution_t temp_solution;
    reserve_memory_for_solution(&temp_solution, n);

    copy_solution(&temp_solution, solution1, n);
    copy_solution(solution1, solution2, n);
    copy_solution(solution2, &temp_solution, n);

    free(temp_solution.matrix);
    free(temp_solution.permutation);
}


/// @brief Read file and load it into a solution_t struct
/// @param file_name File to read
/// @param sol Struct to store permutation and matrix
/// @return 0 if all gone well, otherwise 1
int read_file(const char *file_name, solution_t *sol, int *n){
    FILE *f = fopen(file_name, "r");
        if (f == NULL){
        perror("Error opening the file\n");
        return 1;
    } 
    printf("File oppened!\n");

    // read n value
    fscanf(f, "%d", n);

    // reserve memory for the solution
    reserve_memory_for_solution(sol, (*n));

    // read permutation matrix from file and initialize the permutation
    for(int i = 0; i<sol->n; i++){
        sol->permutation[i] = i;
        for(int j= 0; j<sol->n; j++)
            fscanf(f, "%d", &(sol->matrix[i*(*n)+j]));
    }

    return 0;
}

/// @brief Print matrix
/// @param n Number of rows and columns
/// @param matrix Matrix to print
void print_matrix(int n, int *matrix){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++)
            printf("%d ", matrix[i*n+j]);
        printf("\n");
    }
    printf("\n");
}


/// @brief Print array
/// @param array Array to print
/// @param n Number of elements of the array
void print_array(int *array, int n){
    for(int i = 0; i<n; i++)
        printf("%d ", array[i]);
    printf("\n\n");
}


/// @brief Print solution permutation and matrix
/// @param solution Solution to print
/// @param n Number of elements
void print_solution(solution_t *solution, int n){
    printf("============\nPrinting solution.\n");
    print_array(solution->permutation, n);
    print_matrix(n, solution->matrix);
}


/// @brief Print results on objective function of each solution in the population
/// @param population Population to print results
/// @param n_population Number of solutions on population
void print_results(population_t *population, int n_population, int step){
    printf("Results on step %d: ", step);
    for(int i = 0; i<n_population; i++)
        printf("%d, ", population->population[i].obj_func_value);
    printf("\n\n");
}


/// @brief Objective function for LOP problem
/// @param sol Structure with information to compute and store the objective function
/// @param n Number of elements
void LOP_objective_function(solution_t *sol, int n){
    sol->obj_func_value = 0;
    for(int i = 0; i<n/2; i++)
        for(int j = i+1; j<n; j++)
            sol->obj_func_value += sol->matrix[i*n+j];
    sol->obj_func_computed=1;
}

/// @brief Swap values on permutation of solution_t. Cost O(1)
/// @param solution Solution_t structure with the permutation
/// @param n Number of elements
/// @param s1 First index to swap
/// @param s2 Second index to swap
void swap_permutation(solution_t *solution, int n, int s1, int s2){
    // swap permutation | O(1)
    int tmp = solution->permutation[s1];
    solution->permutation[s1] = solution->permutation[s2];
    solution->permutation[s2] = tmp;
}

/// @brief Swap matrix of Solution_t. Cost O(2N) --> O(N)
/// @param solution Solution_t structure with the permutation
/// @param n Number of elements
/// @param s1 First index to swap
/// @param s2 Second index to swap
void swap_matrix(solution_t *solution, int n, int s1, int s2){
    int *temp = (int *)malloc(n * sizeof(int));
    int tmp;

    // swap matrix | twp phases: O(N) + O(N) = O(2N) === O(N)
    // first phase O(n)
    int i;
    for(i=0; i<n; i++){
        temp[i] = solution->matrix[s1 * n + i];
        solution->matrix[s1 * n + i] = solution->matrix[s2 * n + i];
        solution->matrix[s2 * n + i] = temp[i]; // copy the value, no the pointer
    }

    free(temp); // this pointer can be liberated as values have been copied, no the pointer itself

    for(i = 0; i<n; i++){
        tmp = solution->matrix[i * n + s1];
        solution->matrix[i * n + s1] = solution->matrix[i * n + s2];
        solution->matrix[i * n + s2] = tmp; 
    }    
}

/// @brief Swap operation between two elements. Swaps permutation and matrix. Computational cost: O(2N) --> O(N)
/// @param solution Structure with permutation and matrix to swap
/// @param n Number of elements
/// @param s1 First index to swap with
/// @param s2 Second index to swap with
void swap_op(solution_t *solution, int n, int s1, int s2){
    // swap the permutation
    swap_permutation(solution, n, s1, s2);
    // swap the matrix
    swap_matrix(solution, n, s1, s2);
}

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
        
        for(j=0; j<(n*125); j++){
            index1 = rand() % n;
            index2 = rand() % n;
            swap_op(&(population->population[i]), n, index1, index2);
        }
    }
}

/**
 * Operadores de Cruce (crossover operators)
 *  */

/// @brief Order crossover operator
/// @param parent1 The first parent to realize the operation
/// @param parent2 The second parent to generate the child
/// @param child Child generated from both parents
/// @param n Number of elements
void cruce_orden(solution_t *parent1, solution_t *parent2, solution_t *child, int n){
    int i, j, z;
    int start, end;

    // Initialize child permutation and matrix
    for (i = 0; i < n; i++){
        child->permutation[i] = -1; // Initialize permutation with -1 value on all positions
        for(j=0; j<n; j++)
            child->matrix[i*n+j] = parent1->matrix[i*n+j]; // Initialize matrix with parent1 values (then execute swaps)
    }

    // Take a random range to maintain from the first parent
    start = rand() % n;
    end = start + rand() % (n - start);

    // Copy the range on the child
    for(i=start; i<=end; i++)
        child->permutation[i] = parent1->permutation[i];

    // Fill the rest with values from parent2 in order
    int exists = 0;
    int next_index = (end+1) % n;
    for(i = 0; i<n; i++){ // loop parent2 elements
        int elem = parent2->permutation[(end+1+i)%n];
        exists = 0;

        // Check if the element is already on the child
        for(j=0; j<n; j++)
            if(child->permutation[j]==elem)
                exists = 1;

        // If the element does not exist on child, insert on the next position
        if(exists == 0){
            child->permutation[next_index] = elem;
            next_index = (next_index + 1) % n;
        }
    }

    // Generate parent1 copy
    solution_t parent1_copy;
    reserve_memory_for_solution(&parent1_copy, n);

    // Generate the child matrix running swap operations on parent1
    // Copy parent 1
    copy_solution(&parent1_copy, parent1, n);

    // Swap matrix on child finding differences from parent1
    for(i=0; i<n; i++)
        // if there is a difference between parent and child swap
        if(parent1_copy.permutation[(end + 1 + i) % n] != child->permutation[(end + 1 + i) % n]) // find the value of the child on parent and swap
            for(j=0; j<n; j++)
                if(parent1_copy.permutation[j] == child->permutation[(end+1+i)%n]){
                    //printf("Difference founded on parent (%d) and child (%d)\n", j, (end+i+1)%n);
                    swap_op(&parent1_copy, n, j, (end+1+i)%n);
                    swap_matrix(child, n, j, (end+1+i)%n);
                }

    free(parent1_copy.matrix);
    free(parent1_copy.permutation);
}

void cruce_mapped(){

}

void cruce_ciclos(){

}


/**
 * Selection functions
 */

void ruleta(){

}

void elitista(){

}

/// @brief Tournament to select the parents of the new generation
/// @param selected_parents Indexes of solutions selected as parents
/// @param n_parents Number of parents of the new generation
/// @param population Population of solutions
/// @param k Number of solutions that compite on the tournament to be the parent
/// @param n Number of elements
void tournament(int *selected_parents, int n_parents, population_t *population, int k, int n){
    int *competitors, i, j; // selected solution indexes and amount of selected parents
    competitors = (int *)malloc(k * sizeof(int));
    
    // select n_parents parents
    int n_selected_parents = 0;
    int best_index, best_value;

    // Loop to select n_parents parents
    while(n_selected_parents < n_parents){
        // Initialize competitors
        for(i=0; i<k; i++)
            competitors[i] = -1;

        // select k solutions to compite to be the parent
        i = 0;
        while(i<k){
            int next_selec = rand() % population->n_population; // select an element

            // check if the parent is already a parent or is selected to compite in the tournament
            int founded = 0;

            // check if is selected as competitor
            for(int j=0; j<i; j++){
                if(next_selec == competitors[j])   
                    founded = 1;
            
            // check if is selected as parent
            for(int j = 0; j<n_selected_parents; j++)
                if(next_selec == selected_parents[j])
                    founded=1;
            }

            // if not in any ot both lists, add to competitors list
            if(founded==0){
                competitors[i] = next_selec;
                i++;
            }
        }

        // Tournament: Select the best competitors
        best_index = -1;
        best_value = 0;
        for(i = 0; i<k; i++){
            j = competitors[i]; // get index of competitor

            // if not evaluated, evaluate j. solution
            if(population->population[j].obj_func_computed == 0)
                LOP_objective_function(&(population->population[j]), n);
        
            if(population->population[j].obj_func_value >= best_value){ // there can be equal values
                best_value = population->population[j].obj_func_value;
                best_index = j;
            }
        }

        // add the winner of the tournament to the parent list
        selected_parents[n_selected_parents] = best_index;
        n_selected_parents ++;
    }

    // free memory
    free(competitors);
}


/** SELECTION FUNCTIONS */
void elitist_selection(population_t *population, population_t *new_population, int n, int n_population){
    // compare
    int *selected_children = (int *)malloc(n_population * sizeof(int));

    // Change the worst on population by the best on new_population if is better
    int improvement = 1, worst_index, best_index, worst_value, best_value;
    int i;

    while(improvement==1){
        // find the worst on population and the best on new_population
        best_index = -1, worst_index = -1, worst_value = 999999999, best_value = -1;
        for(i=0; i<n_population; i++){
            if(population->population[i].obj_func_value < worst_value){
                worst_index = i;
                worst_value = population->population[i].obj_func_value;
            }

            if(new_population->population[i].obj_func_value > best_value){
                best_index = i;
                best_value = new_population->population[i].obj_func_value;
            }        
        }

        // compare both, if new population one is better, change
        if(worst_value < best_value){
            //printf("Changing\n");
            //printf("Worst (index, value) = (%d, %d), best (index, value) = (%d, %d)\n", worst_index, worst_value, best_index, best_value);
            exchange_solutions(&(population->population[worst_index]), &(new_population->population[best_index]), n);
        }
        else{
            improvement = 0; // no more improvements can be done
        }
    }
    free(selected_children);
}

/**
 * GENETIC ALGORITHM CODE
 *  */
void GA(population_t *population, int n, int n_population){ // pasar operadores de cruce y mutación?
    // Algorithm loop
    
    int steps = 10;
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
        printf("Tournament passed\n");

        // Generate the new population by crossover and mutation operations
        for(i=0; i<n_population; i++){
            cruce_orden(&(population->population[i_parents[0]]), &(population->population[i_parents[1]]), &(child_population.population[i]), n);
            printf("%d cruce passed\n", i);
            
            int s1, s2;
            s1 = rand() % n;
            s2 = rand() % n;
            swap_op(&(child_population.population[i]), i, s1, s2);
            printf("%d swap passed\n", i);
        }
        
        // Compute objective function values
        for(i = 0; i<n_population; i++){
            //if(population->population[i].obj_func_computed==0)
                LOP_objective_function(&(population->population[i]), n);

            //if(child_population.population[i].obj_func_computed==0)
                LOP_objective_function(&(child_population.population[i]), n);
        }

        print_results(population, n_population, step);

        printf("=================\n=================\n");
        printf("Print population\n");
        for(i = 0; i<n_population; i++){
            printf("Solution %d, obj. value %d, permutation: ", i, population->population[i].obj_func_value);
            for(j=0; j<n; j++){
                printf("%d ", population->population[i].permutation[j]);
            }
            printf("\n");
        }

        /*for(i = 0; i<n_population; i++){
            print_matrix(n, population->population[i].matrix);
        }*/

        printf("\n\n");
        
        printf("Print child population\n");
        for(i = 0; i<n_population; i++){
            printf("Solution %d, obj. value %d, permutation: ", i, child_population.population[i].obj_func_value);
            for(j=0; j<n; j++){
                printf("%d ", child_population.population[i].permutation[j]);
            }
            printf("\n");
        }
        //printf("\n\n");

        // Selection of the new population
        elitist_selection(population, &child_population, n, n_population);
        printf("Elitism passed\n");
        // Not really necessary
        /*for(i = 0; i<n_population; i++){
            if(population->population[i].obj_func_computed==0)
                LOP_objective_function(&(population->population[i]), n);
        }*/

        printf("=================\n");

        
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

        printf("=================\n=================\n");
        /*if(step % 10 == 0){
            printf("Solutions in step %d: ", step);
            for(i = 0; i<n_population; i++)
                printf("%d ", population->population[i].obj_func_value);
            printf("\n");
        }*/
    }
}


int main(int argc, char *argv[]){

    int *solution = NULL, *matrix = NULL; // solution es la permutación que le corresponde a la solución, matrix su matriz
    int n; // cantidad de filas y columnas de la matriz
    int n_population = 5;

    solution_t sol;
    population_t population;


    // read file and load initial solution
    read_file(argv[1], &sol, &n);
    printf("n: %d\n\n", n);

    //print_array(sol.permutation, sol.n);
    //print_matrix(sol.n, sol.matrix);


    // Generate new solutions for the population
    printf("Generating new solutions for the initial population\n");
    reserve_memory_for_population(&population, n, n_population);
    generate_new_instance(&population, &sol, sol.n, n_population);

    /*for(int i = 0; i<n_population; i++){
        print_array(population.population[i].permutation, sol.n);
        print_matrix(sol.n, population.population[i].matrix);
        printf("=========\n");
    }*/

    /* TESTING CUTRE  -->  SWAP WORKS CORRECTLY*/
    // swap
    /*print_solution(&sol, n);

    // swap
    swap_op(&sol, n, 0, 1);
    print_solution(&sol, n);

    // restore
    swap_op(&sol, n, 0, 1);
    print_solution(&sol, n);

    swap_op(&sol, n, 0, 9);
    print_solution(&sol, n);*/


    /* CRUCE ORDEN  --> ORDER CROSSOVER WORKS CORRECTLY*/
    /*solution_t sol2;
    reserve_memory_for_solution(&sol2, n);

    // copy sol in sol2
    for(int i = 0; i<n; i++){
        sol2.permutation[i] = sol.permutation[i];
        for(int j=0; j<n; j++)
            sol2.matrix[i*n+j] = sol.matrix[i*n+j];
    }

    // swap sol2
    for(int i = 0; i<200; i++){
        int s1 = rand() % n;
        int s2 = rand() % n;
        swap_op(&sol2, n, s1, s2);
    }

    // imprime ambas soluciones
    print_solution(&sol, n);
    print_solution(&sol2, n);


    solution_t child;
    reserve_memory_for_solution(&child, n);

    for(int i = 0; i<50; i++)
        cruce_orden(&sol, &sol2, &child, n);

    // print child
    print_solution(&child, n);*/




    auto begin = std::chrono::high_resolution_clock::now();    
    GA(&population, n, n_population);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}