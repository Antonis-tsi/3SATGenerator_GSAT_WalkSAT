#include <iostream>
#include <vector>
#include "sat_generator.h"
#include "solvers_help_functions.h"  // Includes helper functions


using namespace std;

int main() {
    // Παράμετροι για τη γεννήτρια SAT προβλημάτων
    int variables_num = 5;       // Πλήθος μεταβλητών
    int clauses_num = 20;        // Πλήθος όρων
    double probability_negative = 0.3; // Πιθανότητα εμφάνισης αρνητικού literal
    int problem_num = 5;         // Πλήθος προβλημάτων που θα παραχθούν

    // Γεννήτρια SAT προβλημάτων
    vector<vector<vector<int>>> problems = satgenerator(variables_num, clauses_num, probability_negative, problem_num);
    
    // Εκτύπωση των παραχθέντων SAT προβλημάτων
    cout << "Generated SAT Problems:" << endl;
    printSATProblems(problems);

    // Παράμετροι για όλους τους αλγορίθμους
    int max_flips = 100;       // Μέγιστος αριθμός αλλαγών τιμών ανά προσπάθεια
    int max_tries = 10;        // Μέγιστος αριθμός προσπαθειών για εύρεση λύσης
    double propability_rw = 0.6; // Πιθανότητα για τυχαίο περπάτημα στο GSAT-RW και WalkSAT
    double semi_greedy_a = 0.3;  // Παράμετρος a για τη δημιουργία ημι-άπληστης αρχικής κατάστασης στο WalkSAT

    // Εφαρμογή όλων των αλγορίθμων σε κάθε πρόβλημα
    for (size_t i = 0; i < problems.size(); i++) {
        cout << "Solving Problem " << i + 1 << " using GSAT..." << endl;
        vector<int> gsat_solution = gsat(problems[i], max_flips, max_tries, variables_num);
        if (!gsat_solution.empty()) {
            cout << "GSAT Solution found: ";
            for (int val : gsat_solution) {
                cout << val << " ";
            }
            cout << endl;
            cout << "GSAT Cost: " << clauses_num - number_of_clauses_satisfied_by_assignment(problems[i], gsat_solution) << endl;
        } else {
            cout << "GSAT: No solution found after " << max_tries << " tries." << endl;
        }

        cout << "Solving Problem " << i + 1 << " using GSAT-RW..." << endl;
        vector<int> gsat_rw_solution = gsat_rw(problems[i], max_flips, max_tries, propability_rw, variables_num);
        if (!gsat_rw_solution.empty()) {
            cout << "GSAT-RW Solution found: ";
            for (int val : gsat_rw_solution) {
                cout << val << " ";
            }
            cout << endl;
            cout << "GSAT-RW Cost: " << clauses_num - number_of_clauses_satisfied_by_assignment(problems[i], gsat_rw_solution) << endl;
        } else {
            cout << "GSAT-RW: No solution found after " << max_tries << " tries." << endl;
        }

        cout << "Solving Problem " << i + 1 << " using WalkSAT..." << endl;
        vector<int> walksat_solution = walksat(problems[i], max_flips, max_tries, propability_rw, variables_num);
        if (!walksat_solution.empty()) {
            cout << "WalkSAT Solution found: ";
            for (int val : walksat_solution) {
                cout << val << " ";
            }
            cout << endl;
            cout << "WalkSAT Cost: " << clauses_num - number_of_clauses_satisfied_by_assignment(problems[i], walksat_solution) << endl;
        } else {
            cout << "WalkSAT: No solution found after " << max_tries << " tries." << endl;
        }

        cout << "Solving Problem " << i + 1 << " using WalkSAT with Semi-Greedy Initial Assignment..." << endl;
        vector<int> walksat_semi_greedy_solution = walksat_semi_greedy(problems[i], max_flips, max_tries, propability_rw, variables_num, semi_greedy_a);
        if (!walksat_semi_greedy_solution.empty()) {
            cout << "WalkSAT (Semi-Greedy) Solution found: ";
            for (int val : walksat_semi_greedy_solution) {
                cout << val << " ";
            }
            cout << endl;
            cout << "WalkSAT (Semi-Greedy) Cost: " << clauses_num - number_of_clauses_satisfied_by_assignment(problems[i], walksat_semi_greedy_solution) << endl;
        } else {
            cout << "WalkSAT (Semi-Greedy): No solution found after " << max_tries << " tries." << endl;
        }

        cout << "----------------------------------------" << endl;
    }

    return 0;
}
