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

    *matrix = (int **)malloc(*n * sizeof(int *));
    
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
    printf("\n");
}

void swap_op2(int **solution, int n, int s1, int s2){
    int *temp;// = (int **)malloc(n * sizeof(int *));
    int tmp;

    // first phase O(n)
    temp = solution[s1];
    //free(solution[s1]);
    solution[s1] = solution[s2];
    solution[s2] = temp; // esto no funciona del todo bien

    //free(temp);
    for(int i = 0; i<n; i++){
        tmp = solution[i][s1];
        solution[i][s1] = solution[i][s2];
        solution[i][s2] = tmp; 
    }
}

void insert_op2(int *solution, int n, int row, int position){
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

int main(int argc, char *argv[]){

    int *solution = NULL, *matrix = NULL; // solution es la permutación que le corresponde a la solución, matrix su matriz
    int n; // cantidad de filas y columnas de la matriz

    read_file(argv[1], &solution, &matrix, &n);

    //printf("Printing matrix... \n");
    //print_matrix(n, matrix);
    //printf("Matrix printed!\n");

    int result = LOP_objective_function(matrix, n);
    //printf("Result: %d\n", result);


    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();
    //for(int i = 0; i<10000000; i++)
    swap_op(matrix, n, 0, 2);
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    //printf("Result: %.20f\n", sum);
    
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    print_matrix(n, matrix);



    /*int **ptr_matrix;
    int n2;
    read_file2(argv[1], &n2, &ptr_matrix);
    //print_matrix2(ptr_matrix, n2);

    auto begin2 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<10000000; i++)
        swap_op2(ptr_matrix, n2, 1, 3);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto elapsed2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed2.count() * 1e-9);

    print_matrix2(ptr_matrix, n2);*/

    return 0;
}