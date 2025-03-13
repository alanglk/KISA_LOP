#ifndef SA_HPP
#define SA_HPP

#include <random>
#include <chrono>
#include <memory>  // For smart pointers

#include "LOP.hpp"

enum TUpdateType{
    LINEAR,
    GEOMETRIC,
    LOGARITMIC
};

class SimulatedAnnealing {
public:
    static std::random_device rd;  // Declaración (sin inicializar)
    static std::mt19937 gen;       // Declaración (sin inicializar)
    
    double init_T;
    double beta;
    int N_random_walks;
    int N_random_walk_perturbations;
    int max_chain;
    int max_iter;
    int max_stagnation;
    TUpdateType update_type;
    TNeighborhood neigh_type;
    bool stop = false;

    std::unique_ptr<solution_t> final_x;
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point end_time;

    SimulatedAnnealing(double init_T, double beta, int max_chain, int max_iter, int max_stagnation, TUpdateType update_type, TNeighborhood neigh_type);

    static std::chrono::steady_clock::time_point get_current_time();
    static int get_random_index(int upper_bound);
    static double get_random_prob();
    static std::unique_ptr<solution_t> get_sample_from_newighborhood(const std::unique_ptr<solution_t>& x, TNeighborhood neigh_type);
    static double get_initial_temperature(const std::unique_ptr<solution_t>& initial_solution, int N_random_walks, int N_random_walk_perturbations, double acceptance_rate, TNeighborhood neigh_type);

    double update_T(double T, int iteration);
    void run(const std::unique_ptr<solution_t>& initial_solution);
};


#endif