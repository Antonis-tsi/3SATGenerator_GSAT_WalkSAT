#include "solvers_help_functions.h"
#include <vector>
#include <iostream>

using namespace std;


vector<int> gsat_rw(vector<vector<int>> problem, int maxflips, int maxtries, double propability, int variables_num) {
    vector<int> variables_assigment(variables_num, 0);  // Ανάθεση τιμών στις μεταβλητές (αρχικά όλες μηδέν)
    int current_satisfied_clauses = 0;  // Τρέχων αριθμός ικανοποιημένων όρων
    int clauses_num = problem.size();   // Συνολικός αριθμός όρων
    vector<int> satisfied_clauses_per_flip(variables_num, 0);  // Αριθμός όρων που ικανοποιούνται ανά flip
    int flip_index = 0;  // Δείκτης της μεταβλητής που θα αλλάξει τιμή
    vector<int> unsatisfied_clauses;  // Λίστα με μη ικανοποιημένους όρους
    int rand_clause_index = 0;  // Τυχαίος δείκτης όρου από τη λίστα μη ικανοποιημένων όρων
    int literal_index_in_clause = 0;  // Δείκτης literal μέσα στον όρο
    vector<int> best_variables_assigment(variables_num, 0);  // Η καλύτερη ανάθεση μεταβλητών που έχει βρεθεί
    int best_cost = 0;  // Η καλύτερη (χαμηλότερη) τιμή κόστους που έχει επιτευχθεί

    srand(static_cast<unsigned int>(time(nullptr)));  // Αρχικοποίηση της γεννήτριας τυχαίων αριθμών

    
    for (int i = 0; i < maxtries; i++) {
        variables_assigment = assign_random_values(variables_num);  // Τυχαία αρχική ανάθεση στις μεταβλητές
        // Επανάληψη για τον μέγιστο αριθμό αλλαγών (maxflips) ανά προσπάθεια
        for (int j = 0; j < maxflips; j++) {
            current_satisfied_clauses = number_of_clauses_satisfied_by_assignment(problem, variables_assigment);  // Υπολογισμός ικανοποιημένων όρων

            // Ενημέρωση της καλύτερης ανάθεσης αν βρεθεί καλύτερο αποτέλεσμα
            if (current_satisfied_clauses > best_cost) {
                best_variables_assigment = variables_assigment;
                best_cost = current_satisfied_clauses;
            }

            // Αν όλοι οι όροι ικανοποιούνται, επιστρέφει τη λύση
            if (current_satisfied_clauses == clauses_num) {
                return variables_assigment; // Επιστροφή της λύσης
            } else {
                // Απόφαση για τυχαίο περπάτημα ή άπληστη αλλαγή
                bool do_random_walk = (static_cast<double>(rand()) / RAND_MAX < propability);

                if (!do_random_walk) {
                    // Υπολογισμός ικανοποιημένων όρων ανά flip και επιλογή της καλύτερης αλλαγής
                    satisfied_clauses_per_flip = update_satisfied_clauses_num_per_flip(problem, variables_assigment);
                    flip_index = choose_flip_maximum_satisfied_clauses(satisfied_clauses_per_flip);
                    // Αν η αλλαγή αυξάνει ή διατηρεί τον αριθμό ικανοποιημένων όρων, εκτελείται το flip
                    if (satisfied_clauses_per_flip[flip_index] >= current_satisfied_clauses) {
                        variables_assigment[flip_index] = -variables_assigment[flip_index];
                    }
                } else {
                    // Τυχαίο περπάτημα: επιλογή τυχαίου όρου και τυχαίου literal για αλλαγή
                    unsatisfied_clauses = find_unsatisfied_clauses(problem, variables_assigment);
                    rand_clause_index = rand() % unsatisfied_clauses.size();
                    literal_index_in_clause = rand() % 3;
                    flip_index = abs(problem[unsatisfied_clauses[rand_clause_index]][literal_index_in_clause]) - 1;
                    variables_assigment[flip_index] = -variables_assigment[flip_index];
                    unsatisfied_clauses.clear();  // Εκκαθάριση της λίστας μη ικανοποιημένων όρων
                }
            }
        }
    }

    // Εκτύπωση της καλύτερης ανάθεσης που βρέθηκε αν δεν βρεθεί πλήρης λύση
    cout << "Best gsat-rw assigment found: ";
    for (int val : best_variables_assigment) {
        cout << val << " ";
    }
    cout << "best_cost: " << clauses_num - best_cost << endl;

    return {}; // Επιστρέφει κενό vector αν δεν βρεθεί λύση
}
