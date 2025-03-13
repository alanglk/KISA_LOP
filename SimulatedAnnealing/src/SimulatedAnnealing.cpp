// Simulated Annealing Algorithm (Safe Memory Management)

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <memory> // For smart pointers
#include <fstream>
#include <filesystem>
#include <map>
#include <limits.h>

#include "LOP.hpp"
#include "SimulatedAnnealing.hpp"

using namespace std;
namespace fs = std::filesystem;

// Static definition of the generator
std::random_device SimulatedAnnealing::rd;
std::mt19937 SimulatedAnnealing::gen(SimulatedAnnealing::rd());

// Constructor
SimulatedAnnealing::SimulatedAnnealing(double init_T, double beta, int max_chain, int max_iter, int max_stagnation, TUpdateType update_type, TNeighborhood neigh_type) : 
init_T{init_T}, beta{beta}, max_chain{max_chain}, max_iter{max_iter}, max_stagnation{max_stagnation}, update_type{update_type}, neigh_type{neigh_type}{
    
}


std::chrono::steady_clock::time_point SimulatedAnnealing::get_current_time(){
    return std::chrono::steady_clock::now();
}

// Generate a random value using the Mersenne Twister engine
int SimulatedAnnealing::get_random_index(int upper_bound){
    std::uniform_int_distribution<> distrib(0, upper_bound - 1); // Ensure it's within bounds
    return distrib(gen);                                         // Accessing static gen
}

double SimulatedAnnealing::get_random_prob(){
    std::uniform_real_distribution<double> distrib(0.0, 1.0);
    return distrib(gen); // Accessing static gen
}

/// @brief Generate a neighbor solution
std::unique_ptr<solution_t> SimulatedAnnealing::get_sample_from_newighborhood(const std::unique_ptr<solution_t> &x, TNeighborhood neigh_type){
    auto x_new = copy_solution(x);
    // Swap neighborhood
    int s1 = get_random_index(x_new->n);
    int s2;
    do{
        s2 = get_random_index(x_new->n);
    } while (s1 == s2); // Ensure s1 and s2 are different
    
    if (neigh_type == SWAP)
        swap_op(x_new, s1, s2); // Apply swap
    else if (neigh_type == TWO_OPT)
        two_opt_op(x_new, s1, s2);
    
    // Compute Objective function
    LOP_objective_function(x_new);
    return x_new;
}

// Random walk for initial temperature
double SimulatedAnnealing::get_initial_temperature(const std::unique_ptr<solution_t> &initial_solution, int N_random_walks, int N_random_walk_perturbations, double acceptance_rate, TNeighborhood neigh_type){
    int min_func_value = INT_MAX;
    int max_func_value = INT_MIN;

    // Perform random walk to compute T_0
    for (int i = 0; i < N_random_walks; i++)
    {
        auto temp_solution = copy_solution(initial_solution);
        std::cout << "Random Walk: " << i << " /" << N_random_walks << "\r" << std::flush;

        // Apply random perturbations (random number of swaps)
        int num_perturbations = SimulatedAnnealing::get_random_index(N_random_walk_perturbations) + 1; // Random number of swaps between 1 and 20
        for (int j = 0; j < num_perturbations; ++j)
        {
            auto x_new = SimulatedAnnealing::get_sample_from_newighborhood(temp_solution, neigh_type);
            temp_solution = std::move(x_new);

            // Track min and max objective function values during random walk
            if (temp_solution->obj_func_value < min_func_value)
                min_func_value = temp_solution->obj_func_value;
            if (temp_solution->obj_func_value > max_func_value)
                max_func_value = temp_solution->obj_func_value;
        }
    }

    double T_0 = -(double)(max_func_value - min_func_value) / log(acceptance_rate); // 0.75 acceptance rate
    std::cout << "Heuristic T_0: " << T_0 << " -> [max_func_value: " << max_func_value << " | min_func_value: " << min_func_value << "]" << std::endl;
    return T_0;
}

/// @brief Update temperature
double SimulatedAnnealing::update_T(double T, int iteration){
    double new_T;

    // Linear Update
    if (this->update_type == LINEAR)
        new_T = T - this->beta;

    // Geometric Update
    else if (this->update_type == GEOMETRIC)
        new_T = T * this->beta;

    // Logarithmic Update
    else if (this->update_type == LOGARITMIC)
        new_T = this->init_T / log(static_cast<double>(iteration) + 1.0);

    // Temperature Conditions
    if (new_T <= 0.0)
    {
        new_T = 0.0;
        this->stop = true;
    }

    return new_T;
}

/// @brief Run Simulated Annealing Algorithm
/// @param initial_solution
void SimulatedAnnealing::run(const std::unique_ptr<solution_t> &initial_solution)
{
    // Define variables and compute initial objective function value
    double T_k = this->init_T;

    auto x = copy_solution(initial_solution);
    LOP_objective_function(x);

    // Register start time
    this->start_time = SimulatedAnnealing::get_current_time();

    // The algorithm
    double last_obj_value = x->obj_func_value;
    int stagnation_count = 0;
    int num_iter = 0;
    std::cout << "Iteration: " << num_iter << " T_k: NaN chain_size: " << this->max_chain << " stagnation: " << stagnation_count << " OFV: " << x->obj_func_value << std::endl;
    while (num_iter < this->max_iter && !this->stop){
        int chain_size = 0;

        while (chain_size < this->max_chain){
            auto x_new = SimulatedAnnealing::get_sample_from_newighborhood(x, this->neigh_type);
            double delta_f = x->obj_func_value - x_new->obj_func_value;

            if (delta_f < 0){
                // Accept solution
                x = std::move(x_new);
            }
            else if (T_k > 0){
                double I = SimulatedAnnealing::get_random_prob();
                if (exp(-delta_f / T_k) > I)
                    x = std::move(x_new);
            }

            // std::cout << "ch_size: " << chain_size << "x objective function: " << x->obj_func_value << endl;
            chain_size++;
        }
        num_iter++;
        std::cout << "Iteration: " << num_iter << " T_k: " << T_k << " chain_size: " << this->max_chain << " stagnation: " << stagnation_count << " OFV: " << x->obj_func_value << std::endl;
        T_k = this->update_T(T_k, num_iter);

        // Stagnation
        if (x->obj_func_value == last_obj_value)
            stagnation_count++;
        else
            stagnation_count = 0;

        last_obj_value = x->obj_func_value;
        if (this->max_stagnation != -1 & stagnation_count >= this->max_stagnation){
            this->stop = true;
            std::cout << "Stagnation Stop. Solution reached for " << this->max_stagnation << " iterations." << std::endl;
        }
    }

    this->end_time = SimulatedAnnealing::get_current_time();
    // Store the final solution
    this->final_x = std::move(x);
}
