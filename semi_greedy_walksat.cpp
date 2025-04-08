#include "solvers_help_functions.h"
#include <vector>
#include <iostream>

using namespace std;

vector<int> walksat_semi_greedy(vector<vector<int>> problem, int maxflips, int maxtries, double propability, int variables_num, double a) {
    vector<int> variables_assigment(variables_num, 0);
    int current_satisfied_clauses = 0;
    int clauses_num = problem.size();
    int rand_clause_index = 0;
    int literal_index_in_clause = 0;
    vector<int> best_variables_assigment(variables_num, 0);
    int best_cost=0;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < maxtries; i++) {
        // Use semi-greedy initial assignment
        variables_assigment = semi_greedy_initial_assignment(problem, variables_num, a);

        for (int j = 0; j < maxflips; j++) {
            current_satisfied_clauses = number_of_clauses_satisfied_by_assignment(problem, variables_assigment);
            if(current_satisfied_clauses>best_cost){
                best_variables_assigment=variables_assigment;
                best_cost=current_satisfied_clauses;
            }
            if (current_satisfied_clauses == clauses_num) {
                return variables_assigment; // Return solution
            }

            vector<int> unsatisfied_clauses = find_unsatisfied_clauses(problem, variables_assigment);
            

            rand_clause_index = rand() % unsatisfied_clauses.size();
            vector<int> random_clause = problem[unsatisfied_clauses[rand_clause_index]];

            bool do_random_walk = (static_cast<double>(rand()) / RAND_MAX < propability);

            if (do_random_walk) {
                // Randomly pick a variable from the unsatisfied clause
                literal_index_in_clause = abs(random_clause[rand() % 3]) - 1;
            } else {
                // Choose the best variable to flip in the clause
                literal_index_in_clause = choose_best_flip_in_clause(random_clause, update_satisfied_clauses_num_per_flip(problem, variables_assigment));
            }

            // Flip the selected variable
            variables_assigment[literal_index_in_clause] = -variables_assigment[literal_index_in_clause];
        }
    }
    cout << "Best semi-greedy walksat assigment found: ";
            for (int val : best_variables_assigment) {
                cout << val << " ";
            }
    cout<<"best_cost:"<<clauses_num - best_cost<<endl;
    return {}; // Return empty vector if no solution is found
}
