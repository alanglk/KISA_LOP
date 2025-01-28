#include "GA/population_selection.hpp"

#include <iostream>
#include <memory>
#include <stdio.h>


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
