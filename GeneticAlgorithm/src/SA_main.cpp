// Simulated Anealing Algorithm

#include <iostream>
#include <random>
#include <chrono>

#include "IO.hpp"
#include "LOP.hpp"
#include "memory.hpp"

using namespace std;

enum TUpdateType{
    LINEAR,
    GEOMETRIC,
    LOGARITMIC
};

class SimulatedAnnealing{
    private:
        std::random_device rd; // Random device for seeding
        std::mt19937 gen;      // Mersenne Twister random number generator
        bool stop = false;
        chrono::steady_clock::time_point start_time;

    public:
        double init_T;              // Initial temperature
        double beta;                // Beta parameter for T update
        int max_chain;              // Maximun chain size        
        int max_iter;               // Max num of iterations
        TUpdateType update_type;    // Temperature update type
        solution_t final_x;         // computed solution
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    SimulatedAnnealing(double init_T, double beta, int max_chain, int max_iter, TUpdateType update_type): 
        init_T{init_T}, max_chain{max_chain}, max_iter{max_iter}, update_type{update_type}, gen(rd()) {

    }

    chrono::steady_clock::time_point get_current_time(){
        return chrono::steady_clock::now();
    }

    // Generate a random value using the Mersenne Twister engine
    int get_random_index(int upper_bound) {
        std::uniform_int_distribution<> distrib(0, upper_bound);
        return distrib(this->gen); 
    }
    double get_random_prob(){
        std::uniform_real_distribution<double> distrib(0.0, 1.0);
        return distrib(this->gen);
    }

    /// @brief 
    /// @param n lenght of the permutation 
    /// @return neigh
    solution_t get_sample_from_newighborhood(solution_t *x){
        solution_t x_new;
        reserve_memory_for_solution(&x_new, x->n);

        // Uniformly at random choose a solution x_new from N(x)
        copy_solution(&x_new, x, x->n);
        
        // Swap neighborhoodness
        int s1 = this->get_random_index(x_new.n);
        int s2 = this->get_random_index(x_new.n);
        swap_op(&x_new, x_new.n, s1, s2);
        
        // Compute Objective function
        LOP_objective_function(&x_new, x_new.n);
        return x_new;
    }

    /// @brief Update temperature
    double update_T(double T, int iteration){
        double new_T;

        // Linear Update
        if(this->update_type == LINEAR)
            new_T = T - this->beta;
        
        // Geometric Update
        if(this->update_type == GEOMETRIC)
            new_T = T - this->beta;

        
        // Logaritmic Update
        if(this->update_type == LOGARITMIC)
            new_T = this->init_T / log(((double) iteration));

        // Temperature Conditions
        if (new_T <= 0.0){
            new_T = 0.0;
            this->stop = true;
        }

        // Return T value
        return new_T;
    }

    /// @brief Run Simulated Annealing Algorithm
    /// @param initial_solution
    void run(solution_t &initial_solution){
        
        // Define variables and ompute initial objective function value.
        // Then set the initial solution as x.
        double T_k = this->init_T;
        solution_t x;
        LOP_objective_function(&initial_solution, initial_solution.n);
        copy_solution(&x, &initial_solution, initial_solution.n);

        // Initial conditions
        

        // register start time
        this->start_time = this->get_current_time();

        // The algorithm
        int num_iter = 0;
        while(num_iter < this->max_iter){
            int chain_size = 0;

            while(chain_size < this->max_chain){
                solution_t x_new = this->get_sample_from_newighborhood(&x);
                double delta_f = x_new.obj_func_value - x.obj_func_value; 

                if (delta_f < 0){
                    x = x_new;
                }else{
                    double I = this->get_random_prob();
                    if (exp(-delta_f/ T_k)  > I)
                        x = x_new;
                }


                chain_size++;
            }
            
            num_iter++;
            T_k = this->update_T(T_k, num_iter);
        }

    }
};

int main(int argc, char *argv[]){
    std::cout << "Goku, esta vaina e seria." << std::endl;

    int n;
    solution_t solution;
    read_file(argv[1], &solution, &n);
    std::cout << solution;


    SimulatedAnnealing SA = {10000, 0.2, 100, 100, LINEAR};
    SA.run(solution);


    return 0;
}