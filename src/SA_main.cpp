// Simulated Annealing Algorithm (Safe Memory Management)

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <memory>  // For smart pointers
#include <fstream>
#include <filesystem>

#include <limits.h>

using namespace std;
namespace fs = std::filesystem;

struct solution_t {
    vector<int> permutation;
    vector<int> matrix;
    int n;
    int obj_func_value;
};

std::ostream& operator<<(std::ostream& os, const solution_t& sol) {
    // Print the permutation vector
    os << "Permutation: ";
    for (int i = 0; i < sol.n; ++i) {
        os << sol.permutation[i] << " ";
    }
    os << "\n";

    // // Print the matrix in a matrix-like form
    // os << "Matrix: \n";
    // for (int i = 0; i < sol.n; ++i) {
    //     for (int j = 0; j < sol.n; ++j) {
    //         os << sol.matrix[i * sol.n + j] << " ";
    //     }
    //     os << "\n";
    // }

    // Print the objective function value
    os << "Objective Function Value: " << sol.obj_func_value << "\n";

    return os;
}

void LOP_objective_function(const std::unique_ptr<solution_t>& sol){
    sol->obj_func_value = 0;
    for(int i = 0; i< ( sol->n ); i++)
        for(int j = i+1; j< sol->n; j++)
            sol->obj_func_value += sol->matrix[i*sol->n+j];
}

/// @brief  Read LOP initial solution
/// @return 0 if all OK; 1 if not
int read_from_file(fs::path file_path, const std::unique_ptr<solution_t>& sol){
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return 1;
    }

    file >> sol->n;
    sol->permutation.resize(sol->n);
    sol->matrix.resize(sol->n * sol->n);

    // Initialize permutation
    for (int i = 0; i < sol->n; i++) {
        sol->permutation[i] = i;
    }

    // Read matrix values
    for (int i = 0; i < sol->n; i++) {
        for (int j = 0; j < sol->n; j++) {
            file >> sol->matrix[i * sol->n + j];
        }
    }

    file.close();
    
    LOP_objective_function(sol);
    return 0;
}

/// @brief Swap operation between two elements. Swaps permutation and matrix.
/// @param solution Structure with permutation and matrix to swap
/// @param s1 First index to swap with
/// @param s2 Second index to swap with
void swap_op(const std::unique_ptr<solution_t>& solution, int s1, int s2) {
    if (s1 == s2) return;  // No need to swap if indices are the same

    // Swap permutation
    std::swap(solution->permutation[s1], solution->permutation[s2]);

    // Swap corresponding rows in the matrix
    for (int j = 0; j < solution->n; j++) {
        std::swap(solution->matrix[s1 * solution->n + j], solution->matrix[s2 * solution->n + j]);
    }

    // Swap corresponding columns in the matrix
    for (int i = 0; i < solution->n; i++) {
        std::swap(solution->matrix[i * solution->n + s1], solution->matrix[i * solution->n + s2]);
    }
}

std::unique_ptr<solution_t> copy_solution(const std::unique_ptr<solution_t>& original) {
    // Create a new solution instance
    auto new_solution = std::make_unique<solution_t>();
    new_solution->n = original->n;
    new_solution->obj_func_value = original->obj_func_value;
    new_solution->permutation = original->permutation;
    new_solution->matrix = original->matrix;
    return new_solution;  
}

enum TUpdateType{
    LINEAR,
    GEOMETRIC,
    LOGARITMIC
};

class SimulatedAnnealing{
    private:
        static std::random_device rd; // Random device for seeding (static)
        static std::mt19937 gen;      // Mersenne Twister random number generator (static)

    public:
        double init_T;              // Initial temperature
        double beta;                // Beta parameter for T update
        
        int N_random_walks;
        int N_random_walk_perturbations;

        int max_chain;              // Maximum chain size        
        int max_iter;               // Max num of iterations
        
        TUpdateType update_type;    // Temperature update type
        
        bool stop = false;

        std::unique_ptr<solution_t> final_x;  // Computed solution

        chrono::steady_clock::time_point start_time;
        chrono::steady_clock::time_point end_time;

    SimulatedAnnealing(double init_T, double beta, int max_chain, int max_iter, TUpdateType update_type): 
        init_T{init_T}, beta{beta}, max_chain{max_chain}, max_iter{max_iter}, update_type{update_type} {
            // Constructor
        }

    static chrono::steady_clock::time_point get_current_time(){
        return chrono::steady_clock::now();
    }

    // Generate a random value using the Mersenne Twister engine
    static int get_random_index(int upper_bound) {
        std::uniform_int_distribution<> distrib(0, upper_bound - 1); // Ensure it's within bounds
        return distrib(gen);  // Accessing static gen
    }

    static double get_random_prob(){
        std::uniform_real_distribution<double> distrib(0.0, 1.0);
        return distrib(gen); // Accessing static gen
    }

    /// @brief Generate a neighbor solution
    static std::unique_ptr<solution_t> get_sample_from_newighborhood(const std::unique_ptr<solution_t>& x){
        auto x_new = copy_solution(x);

        // Swap neighborhood
        int s1 = get_random_index(x_new->n);
        int s2;
        do {
            s2 = get_random_index(x_new->n);
        } while (s1 == s2);  // Ensure s1 and s2 are different

        swap_op(x_new, s1, s2); // Apply swap

        // Compute Objective function
        LOP_objective_function(x_new);
        return x_new;
    }

    // Random walk for initial temperature
    static double get_initial_temperature(const std::unique_ptr<solution_t>& initial_solution, int N_random_walks, int N_random_walk_perturbations, double acceptance_rate){
        int min_func_value = INT_MAX;
        int max_func_value = INT_MIN;

        // Perform random walk to compute T_0
        for (int i = 0; i < N_random_walks; i++) {
            auto temp_solution = copy_solution(initial_solution);
            std::cout << "Random Walk: " << i << " /" << N_random_walks << "\r" << std::flush;

            // Apply random perturbations (random number of swaps)
            int num_perturbations = SimulatedAnnealing::get_random_index(N_random_walk_perturbations) +1;  // Random number of swaps between 1 and 20
            for (int j = 0; j < num_perturbations; ++j) {
                auto x_new = SimulatedAnnealing::get_sample_from_newighborhood(temp_solution);
                temp_solution = std::move(x_new);
                
                // Track min and max objective function values during random walk
                if (temp_solution->obj_func_value < min_func_value)
                    min_func_value = temp_solution->obj_func_value;
                if (temp_solution->obj_func_value > max_func_value)
                    max_func_value = temp_solution->obj_func_value;
            }
        }

    double T_0 = - (double)(max_func_value - min_func_value) / log(acceptance_rate); // 0.75 acceptance rate
    std::cout << "Heuristic T_0: " << T_0 << " -> [max_func_value: " << max_func_value << " | min_func_value: " << min_func_value << "]" << std::endl;
    return T_0;

    }

    /// @brief Update temperature
    double update_T(double T, int iteration){
        double new_T;

        // Linear Update
        if(this->update_type == LINEAR)
            new_T = T - this->beta;
        
        // Geometric Update
        else if(this->update_type == GEOMETRIC)
            new_T = T * this->beta;

        // Logarithmic Update
        else if(this->update_type == LOGARITMIC)
            new_T = this->init_T / log(static_cast<double>(iteration) + 1.0);

        // Temperature Conditions
        if (new_T <= 0.0){
            new_T = 0.0;
            this->stop = true;
        }

        return new_T;
    }

    /// @brief Run Simulated Annealing Algorithm
    /// @param initial_solution
    void run(const std::unique_ptr<solution_t>& initial_solution){
        // Define variables and compute initial objective function value
        double T_k = this->init_T;

        auto x = copy_solution(initial_solution);
        LOP_objective_function(x);

        // Register start time
        this->start_time = SimulatedAnnealing::get_current_time();

        // The algorithm
        int num_iter = 0;
        while(num_iter < this->max_iter && !this->stop){
            int chain_size = 0;
            
            std::cout << "Iteration: " << num_iter << " T_k: " << T_k << " Objective Function Value: " << x->obj_func_value << std::endl;
            while(chain_size < this->max_chain){
                auto x_new = SimulatedAnnealing::get_sample_from_newighborhood(x);
                double delta_f = x_new->obj_func_value - x->obj_func_value; 

                if (delta_f < 0){
                    x = std::move(x_new);
                }else{
                    double I = SimulatedAnnealing::get_random_prob();
                    if (exp(-delta_f / T_k) > I)
                        x = std::move(x_new);
                }

                // std::cout << "ch_size: " << chain_size << "x objective function: " << x->obj_func_value << endl;
                chain_size++;
            }
            
            num_iter++;
            T_k = this->update_T(T_k, num_iter);

            // std::cout << endl;
        }

        this->end_time = SimulatedAnnealing::get_current_time();
        // Store the final solution
        this->final_x = std::move(x);
    }
};
// Static definition of the generator
std::random_device SimulatedAnnealing::rd;
std::mt19937 SimulatedAnnealing::gen(SimulatedAnnealing::rd()); 



int main(int argc, char *argv[]){
    std::cout << "Goku, esta vaina e seria." << std::endl;

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return EXIT_FAILURE;
    }

    int n;
    auto initial_solution = std::make_unique<solution_t>();

    read_from_file(argv[1], initial_solution);
    std::cout << "\nInitial Solution:\n" << *initial_solution << std::endl << std::endl;
    
    
    int N_iterations = 100;
    int N_chain = 100;      // max chain
    double T_0 = 74933.4;   // Fixed initial temp
    double beta = T_0 / N_iterations;

    // Heuristic initial temp
    int N_random_walks = 10000; 
    int N_random_walk_perturbations = 100;
    double acceptance_rate = 0.75;
    // T_0 = SimulatedAnnealing::get_initial_temperature(initial_solution, N_random_walks, N_random_walk_perturbations, acceptance_rate);


    std::cout << "Parameters for Simulated Annealing Algorithm:" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Number of iterations: " << N_iterations << std::endl;
    std::cout << "Maximum chain size: " << N_chain << std::endl;
    std::cout << "Initial temperature (T_0): " << T_0 << std::endl;
    std::cout << "Beta (T_0 / N_iterations): " << beta << std::endl;
    std::cout << "Number of random walks: " << N_random_walks << std::endl;
    std::cout << "Number of perturbations per random walk: " << N_random_walk_perturbations << std::endl;
    std::cout << "Acceptance rate: " << acceptance_rate << std::endl;

    SimulatedAnnealing SA(T_0, beta, N_chain, N_iterations, LINEAR);
    SA.run(initial_solution);
    
    std::cout << "\nFinal solution:\n" << *SA.final_x << std::endl << std::endl;

    return 0;
}