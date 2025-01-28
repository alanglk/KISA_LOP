#include "include/GA/parent_selection.hpp"

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
