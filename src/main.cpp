#include <iostream>
#include <memory>
#include <stdio.h>
#include <chrono>
#include "include/common.hpp"

/// @brief Read file and load it into a matrix
/// @param file_name File to read
/// @param n Number of rows and colums 
/// @param matrix The matrix to load the file in there
/// @return 
int read_file(const char *file_name, int *n, int **matrix){
    FILE *f = fopen(file_name, "r");
        if (f == NULL){
        perror("Error opening the file\n");
        return 1;
    } 

    printf("File oppened\n");
    fscanf(f, "%d", n);

    printf("%d\n", *n);

    *matrix = (int *)malloc((*n) * (*n) * sizeof(int));

    for (int i = 0; i<(*n)*(*n); i++){
        fscanf(f, "%d", &(*matrix)[i]);
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


/**
 * FIRST ALGORITHM CODE
 */

/**
 * GENETIC ALGORITHM CODE
 *  */
void GA(int *instance, int n, int n_poblacion){
    // Generate initial poblation from instance


    // Algorithm loop
    while(true){
        // Crossover

        // Mutation

        // Selection
    }

}

void generate_initial_population(int *instance, int n){

}

// Crossovers
void cruce_orden(){

}

void cruce_mapped(){

}

void cruce_ciclos(){

}

// Mutations
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
            for(int j = 0; j<n; j++)
                solution[i*n+j] = solution[(i+1)*n + j];
        }
    }
    else{
        for(i = row; i>position; i--){
            for(int j = 0; j<n; j++)
                solution[i*n+j] = solution[(i-1)*n + j];
        }
    }
    for(i = 0; i<n; i++){
        solution[position*n+i] = temp[i]; // guarda el 
    }

    free(temp);

    // SEGUNDA FASE
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

void inversion(){

}

void scramble(){

}


// SECOND OPTION
int read_file2(const char *file_name, int *n, int ***matrix){
    FILE *f = fopen(file_name, "r");
        if (f == NULL){
        perror("Error opening the file\n");
        return 1;
    } 

    printf("File oppened\n");
    fscanf(f, "%d", n);

    printf("%d\n", *n);

    int i;

    *matrix = (int **)malloc(*n * sizeof(int));
    
    for(i = 0; i<(*n); i++)
        (*matrix)[i] = (int *)malloc(*n * sizeof(int));

    for (int i = 0; i<(*n); i++)
        for(int j = 0; j<(*n); j++)
            fscanf(f, "%d", &((*matrix)[i][j]));

    return 0;
}

void print_matrix2(int **matrix, int n){
    for(int i = 0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void swarp_op2(int **solution, int n, int s1, int s2){
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

void insert_op2(){

}

int main(int argc, char *argv[]){
    std::cout << "Hello World!" << std::endl;

    /*int *matrix = NULL;
    int n;

    read_file(argv[1], &n, &matrix);

    //printf("Printing matrix... \n");
    //print_matrix(n, matrix);
    //printf("Matrix printed!\n");

    int result = LOP_objective_function(matrix, n);
    //printf("Result: %d\n", result);


    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();
    insert_op(matrix, n, 0, 50);
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    //printf("Result: %.20f\n", sum);
    
    //printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    //print_matrix(n, matrix);


*/
    int **ptr_matrix;
    int n;
    read_file2(argv[1], &n, &ptr_matrix);
    print_matrix2(ptr_matrix, n);


    return 0;
}

