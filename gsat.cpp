#include "solvers_help_functions.h"
#include <vector>
#include <iostream>

using namespace std;


vector<int> gsat(vector<vector<int> > problem, int maxflips, int maxtries, int variables_num) {
    
    vector<int> variables_assigment(variables_num, 0);  // Ανάθεση τιμών στις μεταβλητές (αρχικά όλες μηδέν)
    int current_satisfied_clauses = 0;  // Τρέχων αριθμός ικανοποιημένων όρων
    int clauses_num = problem.size();   // Συνολικός αριθμός όρων
    vector<int> satisfied_clauses_per_flip(variables_num, 0);  // Αριθμός ικανοποιημένων όρων ανά flip
    int flip_index = 0;  // Δείκτης της μεταβλητής που θα αλλάξει τιμή
    vector<int> best_variables_assigment(variables_num, 0);  // Καλύτερη ανάθεση μεταβλητών που έχει βρεθεί
    int best_cost = 0;  // Καλύτερη τιμή κόστους (αριθμός ικανοποιημένων όρων)

    
    for (int i = 0; i < maxtries; i++) {
        variables_assigment = assign_random_values(variables_num);  // Τυχαία αρχική ανάθεση τιμών στις μεταβλητές

        
        for (int j = 0; j < maxflips; j++) {
            current_satisfied_clauses = number_of_clauses_satisfied_by_assignment(problem, variables_assigment);  // Υπολογισμός των ικανοποιημένων όρων

            // Αν βρεθεί καλύτερη ανάθεση, ενημερώνεται η καλύτερη ανάθεση και το κόστος
            if (current_satisfied_clauses > best_cost) {
                best_variables_assigment = variables_assigment;
                best_cost = current_satisfied_clauses;
            }

            // Αν όλοι οι όροι ικανοποιούνται, επιστρέφει τη λύση
            if (current_satisfied_clauses == clauses_num) {
                return variables_assigment;  // Επιστροφή της λύσης
            } else {
                // Υπολογισμός των ικανοποιημένων όρων ανά flip
                satisfied_clauses_per_flip = update_satisfied_clauses_num_per_flip(problem, variables_assigment);

                // Επιλογή της μεταβλητής που θα αλλάξει τιμή για μέγιστη ικανοποίηση όρων
                flip_index = choose_flip_maximum_satisfied_clauses(satisfied_clauses_per_flip);

                // Αν η αλλαγή αυξάνει ή διατηρεί τον αριθμό των ικανοποιημένων όρων, εκτελεί το flip
                if (satisfied_clauses_per_flip[flip_index] >= current_satisfied_clauses) {
                    variables_assigment[flip_index] = -variables_assigment[flip_index];
                }
            }
        }
    }

    // Εκτύπωση της καλύτερης ανάθεσης που βρέθηκε αν δεν βρεθεί πλήρης λύση
    cout << "Best gsat assigment found: ";
    for (int val : best_variables_assigment) {
        cout << val << " ";
    }
    cout << "best_cost: " << clauses_num - best_cost << endl;

    return {};  // Επιστροφή κενού vector αν δεν βρεθεί λύση
}
