#ifndef SOLVERS_HELP_FUNCTIONS_H
#define SOLVERS_HELP_FUNCTIONS_H

#include <vector>

using namespace std;

std::vector<int> gsat(std::vector<std::vector<int> > problem, int maxflips, int maxtries,int variables_num);
vector<int> gsat_rw(vector<vector<int> > problem, int maxflips, int maxtries, double propability, int variables_num);
vector<int> walksat(vector<vector<int> > problem, int maxflips, int maxtries, double propability, int variables_num);
vector<int> walksat_semi_greedy(vector<vector<int> > problem, int maxflips, int maxtries, double propability, int variables_num, double a);
std::vector<int> assign_random_values(int variables_num);
int number_of_clauses_satisfied_by_assignment(std::vector<std::vector<int> > problem, std::vector<int> variables_assigment);
std::vector<int> update_satisfied_clauses_num_per_flip(std::vector<std::vector<int> > problem, std::vector<int> variables_assigment);
int choose_flip_maximum_satisfied_clauses(std::vector<int> satisfied_clauses_per_flip);

std::vector<int> gsat_rw(std::vector<std::vector<int> > current_problem, int max_flips, int max_tries, double probability, int variables_num);
int negative_or_positive_propability(int propability);
vector<int> find_unsatisfied_clauses(vector<vector<int> > problem, vector<int> variables_assigment);

int choose_best_flip_in_clause(vector<int> clause,vector<int> satisfied_clauses_per_flip);
vector<int> semi_greedy_initial_assignment(vector<vector<int> > problem, int variables_num, double a);

#endif // GSAT_H
