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


/// @brief Read file and load it into a matrix
/// @param file_name File to read
/// @param n Number of rows and colums 
/// @param matrix The matrix to load the file in there
/// @return 
int read_file(const char *file_name, int **solution, int **matrix, int *n){
    FILE *f = fopen(file_name, "r");
        if (f == NULL){
        perror("Error opening the file\n");
        return 1;
    } 

    printf("File oppened\n");
    fscanf(f, "%d", n);

    printf("%d\n", *n);

    *solution = (int *)malloc((*n) * sizeof(int));
    for(int i = 0; i<(*n); i++)
        (*solution)[i] = i;

    *matrix = (int *)malloc((*n) * (*n) * sizeof(int));
    for (int i = 0; i<(*n)*(*n); i++){
        fscanf(f, "%d", &(*matrix)[i]);
    }

    return 0;
}

int read_file2(const char *file_name, solution_t *sol){
    FILE *f = fopen(file_name, "r");
        if (f == NULL){
        perror("Error opening the file\n");
        return 1;
    } 

    printf("File oppened\n");
    //*sol = malloc(sizeof(solution_t));
    fscanf(f, "%d", &(sol->n));

    int n = sol->n;

    printf("n: %d\n", n);

    sol->matrix = (int *)malloc(n * n * sizeof(int));
    sol->permutation = (int *)malloc(n * sizeof(int));

    for(int i = 0; i<sol->n; i++){
        sol->permutation[i] = i;
        for(int j= 0; j<sol->n; j++){
            fscanf(f, "%d", &(sol->matrix[i*n+j]));
        }
    }
    return 0;
}

/// @brief Print matrix
/// @param n Number of rows and columns
/// @param matrix Matrix to print
void print_matrix(int n, int *matrix){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            printf("%d ", matrix[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_array(int *array, int n){
    for(int i = 0; i<n; i++){
        printf("%d ", array[i]);
    }
    printf("\n\n");
}


/// @brief Objective function for LOP problem
/// @param matrix Instance to evaluate
/// @param n Number of rows and columns
/// @return Value of the objective function for that instance
int LOP_objective_function(int *matrix, int n){
    int sum = 0;
    for(int i = 0; i<n/2; i++)
        for(int j = i+1; j<n; j++)
            sum += matrix[i*n+j];
    return sum;
}

void LOP_objective_function2(solution_t *sol, int n){
    for(int i = 0; i<n/2; i++)
        for(int j = i+1; j<n; j++)
            sol->obj_func_value += sol->matrix[i*n+j];
    sol->obj_func_computed=1;
}


/**
 * FIRST ALGORITHM CODE
 */


// Mutations --> SEPARARLO EN DOS FUNCIONES PARA NO TENER QUE EJECUTAR LOS IF???
void insert_op(int *solution, int n, int row, int position){
    int *temp = (int *)malloc(n*sizeof(int));
    int tmp;

    //PRIMERA FASE
    // si row > position, se desplaza el resto hacía abajo
    // si row < position, se desplaza el resto hacía arriba
    int i;
    for(i = 0; i<n; i++){
        temp[i] = solution[row*n+i]; // guarda el 
    }
    if(row < position){
        for(i = row; i<position; i++){
            //memcpy((void *)solution[(i+1)*n], (void *)solution[i*n], n*sizeof(int));
            for(int j = 0; j<n; j++)
                solution[i*n+j] = solution[(i+1)*n + j];
        }
    }
    else{
        for(i = row; i>position; i--){
            //memcpy((void *)solution[(i-1)*n], (void *)solution[i*n], n*sizeof(int));

            for(int j = 0; j<n; j++)
                solution[i*n+j] = solution[(i-1)*n + j];
        }
    }
    for(i = 0; i<n; i++){
        solution[position*n+i] = temp[i]; // guarda el 
    }

    free(temp);

    // SEGUNDA FASE
    #pragma omp parallel for
    for(i = 0; i<n; i++){
        tmp = solution[i * n + row]; // store the one that must be moved
                
        if(row < position){
            for(int j = row; j<position; j++){
                solution[i * n + j] = solution[i * n + j + 1];
            }
        }
        else{
            for(int j = row; j>position; j--){
                solution[i * n + j] = solution[i*n + j - 1];
            }
        }
        solution[i*n + position] = tmp;
    }
}

/// @brief Swap operation between two elements. Cost O(2N) --> O(N)
/// @param solution The matrix
/// @param n Number of elements 
/// @param s1 
/// @param s2 
void swap_op(int *solution, int n, int s1, int s2){
    int *temp = (int *)malloc(n * sizeof(int));
    int tmp;
    // first phase O(n)
    int i;
    for(i=0; i<n; i++){
        temp[i] = solution[s1 * n + i];
        solution[s1 * n + i] = solution[s2 * n + i];
        solution[s2 * n + i] = temp[i];
    }

    free(temp);

    for(i = 0; i<n; i++){
        tmp = solution[i * n + s1];
        solution[i * n + s1] = solution[i * n + s2];
        solution[i * n + s2] = tmp; 
    }
}

void swap_op2(solution_t *solution, int n, int s1, int s2){
    int *temp = (int *)malloc(n * sizeof(int));
    int tmp;

    // swap permutation | O(1)
    tmp = solution->permutation[s1];
    solution->permutation[s1] = solution->permutation[s2];
    solution->permutation[s2] = tmp;

    // swap matrix | twp phases: O(N) + O(N) = O(2N) === O(N)
    // first phase O(n)
    int i;
    for(i=0; i<n; i++){
        temp[i] = solution->matrix[s1 * n + i];
        solution->matrix[s1 * n + i] = solution->matrix[s2 * n + i];
        solution->matrix[s2 * n + i] = temp[i];
    }

    free(temp);

    for(i = 0; i<n; i++){
        tmp = solution->matrix[i * n + s1];
        solution->matrix[i * n + s1] = solution->matrix[i * n + s2];
        solution->matrix[i * n + s2] = tmp; 
    }
}

void swap_only_matrix(solution_t *solution, int n, int s1, int s2){
    int *temp = (int *)malloc(n * sizeof(int));
    int tmp;

    // swap matrix | twp phases: O(N) + O(N) = O(2N) === O(N)
    // first phase O(n)
    int i;
    for(i=0; i<n; i++){
        temp[i] = solution->matrix[s1 * n + i];
        solution->matrix[s1 * n + i] = solution->matrix[s2 * n + i];
        solution->matrix[s2 * n + i] = temp[i];
    }

    free(temp);

    for(i = 0; i<n; i++){
        tmp = solution->matrix[i * n + s1];
        solution->matrix[i * n + s1] = solution->matrix[i * n + s2];
        solution->matrix[i * n + s2] = tmp; 
    }    
}

void swap_op_generate_new(int *new_matrix, int *matrix, int n, int s1, int s2){
    int *temp = (int *)malloc(n * sizeof(int));
    int tmp;
    int i;

    // copy
    for(i = 0; i<n; i++){
        for(int j=0; j<n; j++){
            new_matrix[i*n+j] = matrix[i*n+j];
        }
    }

    // first phase O(n)
    for(i=0; i<n; i++){
        temp[i] = new_matrix[s1 * n + i];
        new_matrix[s1 * n + i] = new_matrix[s2 * n + i];
        new_matrix[s2 * n + i] = temp[i];
    }

    free(temp);

    for(i = 0; i<n; i++){
        tmp = new_matrix[i * n + s1];
        new_matrix[i * n + s1] = new_matrix[i * n + s2];
        new_matrix[i * n + s2] = tmp; 
    }
}

/// @brief Generates a new instance by the swap operation
/// @param new_sol New instance generated by swap operation
/// @param sol Base instance to generate the new instance
/// @param n Number of elements in the permutation
/// @param s1 First index for the swap
/// @param s2 Second index for the swap
void swap_op_generate_new2(solution_t *new_sol, solution_t *sol, int n, int s1, int s2){
    int *temp = (int *)malloc(n * sizeof(int));
    int tmp;
    int i;

    // copy
    for(i = 0; i<n; i++){
        new_sol->permutation[i] = sol->permutation[i]; // copy permutation
        for(int j=0; j<n; j++){ 
            new_sol->matrix[i*n+j] = sol->matrix[i*n+j]; // copy matrix
        }
    }
    swap_op2(new_sol, n, s1, s2);
}

void generate_new_variant_from_instance(int ***population, int *init_instance, int n, int n_population){
    *population = (int **)malloc(n_population * sizeof(int *));

    for(int i = 0; i<n_population; i++)
        (*population)[i] = (int *)malloc(n * n * sizeof(int));

    printf("Memory reserved\n");

    int index1;
    int index2;
    for(int i = 0; i<n_population; i++){
        index1 = rand() % n;
        index2 = rand() % n;
        printf("In population memeber %d generating new instance swapping indexed %d and %d...\n", i, index1, index2);
        swap_op_generate_new((*population)[i], init_instance, n, index1, index2);
        printf("Starting process...\n");
        for(int j = 0; j<250; j++){
            index1 = rand() % n;
            index2 = rand() % n;
            swap_op((*population)[i], n, index1, index2);
        }
        printf("%d finished!\n", i);
    }
}

void generate_new_instance(population_t *population, solution_t *init_solution, int n, int n_population){
    population->n_population = n_population;
    population->n = n;

    population->population = (solution_t *)malloc(n_population * sizeof(solution_t));

    // Allocate memory for each solution of the population
    for(int i = 0; i<n_population; i++){
        population->population[i].matrix = (int *)malloc(n * n * sizeof(int));
        population->population[i].permutation = (int *)malloc(n * sizeof(int));
    }

    population->population[0] = *init_solution;


    int index1, index2, i, j;
    for(i=1; i<n_population; i++){
        index1 = rand() % n;
        index2 = rand() % n;
        swap_op_generate_new2(&(population->population[i]), init_solution, n, index1, index2);
        for(j=0; j<250; j++){
            index1 = rand() % n;
            index2 = rand() % n;
            swap_op2(&population->population[i], n, index1, index2);
        }
    }
}

// Crossovers
void cruce_orden(solution_t *parent1, solution_t *parent2, solution_t *child, int n){
    int i, j, z;
    int start, end;

    // initialize child permutation and matrix
    for (i = 0; i < n; i++){
        child->permutation[i] = -1; // initialize permutation with -1 value on all positions
        for(j=0; j<n; j++)
            child->matrix[i*n+j] = parent1->matrix[i*n+j]; // initialize matrix with parent1 values (then execute swaps)
    }

    // Generar índices aleatorios para el rango
    start = rand() % n;
    end = start + rand() % (n - start);

    // copiar el parent1 en el hijo
    for(i=start; i<=end; i++)
        child->permutation[i] = parent1->permutation[i];

    //print_array(child->permutation, n);

    int exists = 0;
    int next_index = (end+1) % n;
    for(i = 0; i<n; i++){
        int elem = parent2->permutation[(end+1+i)%n];
        exists = 0;

        for(j=0; j<n; j++){
            if(child->permutation[j]==elem)
                exists = 1;
        }

        if(exists == 0){
            child->permutation[next_index] = elem;
            next_index = (next_index + 1) % n;
        }
    }

    //print_array(parent1->permutation, n);
    //print_array(parent2->permutation, n);
    //print_array(child->permutation, n);


    // se utiliza la copia para después modificar la matriz
    solution_t parent1_copy;
    parent1_copy.n = parent1->n;
    parent1_copy.matrix = (int *)malloc(n*n*sizeof(int));
    parent1_copy.permutation = (int *)malloc(n*sizeof(int));

    for(i=0; i<n; i++){
        parent1_copy.permutation[i] = parent1->permutation[i];
        for(j=0; j<n; j++)
            parent1_copy.matrix[i*n+j] = parent1->matrix[i*n+j];
    }

    // cruce en matrices
    for(i=0; i<n; i++){
        if(parent1_copy.permutation[(end + 1 + i) % n] != child->permutation[(end + 1 + i) % n]){ // find the value of the child on parent and swap
            for(j=0; j<n; j++){
                if(parent1_copy.permutation[j] == child->permutation[(end+1+i)%n]){
                    //printf("Difference founded on parent (%d) and child (%d)\n", j, (end+i+1)%n);
                    swap_op2(&parent1_copy, n, j, (end+1+i)%n);
                    swap_only_matrix(child, n, j, (end+1+i)%n);
                }
            }
        }
    }

    free(parent1_copy.matrix);
    free(parent1_copy.permutation);

    //print_matrix(n, parent1->matrix);
    //print_matrix(n, child->matrix);
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

void torneo(){

}

/**
 * GENETIC ALGORITHM CODE
 *  */
void GA(population_t population, int n, int n_population){ // pasar operadores de cruce y mutación?
    

    // Algorithm loop
    while(true){
        // Elegir parents


        // Crossover
        //cruce_orden();

        // Mutation
        //swap_op2();

        // Selection
    }

}


int main(int argc, char *argv[]){

    int *solution = NULL, *matrix = NULL; // solution es la permutación que le corresponde a la solución, matrix su matriz
    int n; // cantidad de filas y columnas de la matriz

    /*read_file(argv[1], &solution, &matrix, &n);

    //printf("Printing matrix... \n");
    //print_matrix(n, matrix);
    //printf("Matrix printed!\n");

    int result = LOP_objective_function(matrix, n);
    //printf("Result: %d\n", result);


    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();
    //for(int i = 0; i<10000000; i++)
    //swap_op(matrix, n, 0, 2);
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    //printf("Result: %.20f\n", sum);
    
    //printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    //print_matrix(n, matrix);
    
    // generate new instances
    int **population;
    int n_population = 5;
    generate_new_variant_from_instance(&population, matrix, n, n_population);

    for(int i = 0; i<n_population; i++){
        print_matrix(n, population[i]);
    }


*/

    solution_t sol;
    read_file2(argv[1], &sol);

    printf("n: %d\n\n", sol.n);

    print_array(sol.permutation, sol.n);
    print_matrix(sol.n, sol.matrix);


    population_t population;
    printf("Generating new solutions for the initial population\n");
    generate_new_instance(&population, &sol, sol.n, 5);

    for(int i = 0; i<5; i++){
        print_array(population.population[i].permutation, sol.n);
        print_matrix(sol.n, population.population[i].matrix);
        printf("=========\n");
    }

    solution_t child;
    child.matrix = (int *)malloc(sol.n * sol.n * sizeof(int));
    child.permutation = (int *)malloc(sol.n * sizeof(int));

    auto begin = std::chrono::high_resolution_clock::now();
    //for(int i = 0; i<5000000; i++)
    cruce_orden(&population.population[1], &population.population[2], &child, sol.n);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}

