// Simulated Anealing Algorithm

#include <iostream>
#include "IO.hpp"
#include "LOP.hpp"
#include "memory.hpp"

using namespace std;


class SimulatedAnnealing{
    public:
        double init_T;          // Initial temperature
        int max_chain;          // Maximun chain size        
        int max_iter;           // Max num of iterations
        solution_t x;           // computed solution

    SimulatedAnnealing(double init_T, int max_chain, int max_iter): 
        init_T{init_T}, max_chain{max_chain}, max_iter{max_iter} {
        // Constructor
    }


    /// @brief 
    /// @param n lenght of the permutation 
    /// @return neigh
    solution_t get_sample_from_newighborhood(const solution_t& x){
        solution_t x_new;
        reserve_memory_for_solution(&x_new, x.n);

        // Uniformly at random choose a solution x_new from N(x)
        // mutation.cpp -> copy to LOP.cpp


        // Compute Objective function
        LOP_objective_function(&x_new, x_new.n);
        return x_new;
    }

    /// @brief Run Simulated Annealing Algorithm
    /// @param initial_solution
    void run(solution_t &initial_solution){
        
        // Compute initial objective function value. Then set the initial solution as x.
        LOP_objective_function(&initial_solution, initial_solution.n);
        copy_solution(&this->x, &initial_solution, initial_solution.n);

        // The algorithm
        int num_iter = 0;
        while(num_iter < this->max_iter){
            int chain_size = 0;

            while(chain_size < this->max_chain){
                solution_t x_new = this->get_sample_from_newighborhood(this->x);
                int delta_f = x_new.obj_func_value - this->x.obj_func_value; 

                if (delta_f < 0){
                    this->x = x_new;
                }else{
                    
                }


                chain_size++;
            }


            num_iter++;
        }

    }
};

int main(int argc, char *argv[]){
    std::cout << "Goku, esta vaina e seria." << std::endl;

    int n;
    solution_t solution;
    read_file(argv[1], &solution, &n);
    std::cout << solution;


    SimulatedAnnealing SA = {0.0, 10, 5};
    SA.run(solution);


    return 0;
}