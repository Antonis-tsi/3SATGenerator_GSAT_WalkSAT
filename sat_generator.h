#ifndef SAT_GENERATOR_H
#define SAT_GENERATOR_H

#include <vector>

using namespace std;

vector<vector<vector<int>>> satgenerator(int variables_num, int clauses_num, double probability_negative, int problem_num);
void printSATProblems(const vector<vector<vector<int>>>& problems);

#endif // SAT_GENERATOR_H