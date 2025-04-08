#include "solvers_help_functions.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

// Δημιουργεί μια τυχαία ανάθεση τιμών (-1 ή 1) στις μεταβλητές
vector<int> assign_random_values(int variables_num) {
    vector<int> variables_assigment(variables_num);
    for (int i = 0; i < variables_num; i++) {
        // Κάθε μεταβλητή παίρνει τυχαία την τιμή -1 ή 1
        variables_assigment[i] = (static_cast<double>(rand()) / RAND_MAX < 0.5) ? -1 : 1;
    }
    return variables_assigment;
}

// Υπολογίζει τον αριθμό των όρων που ικανοποιούνται από την τρέχουσα ανάθεση
int number_of_clauses_satisfied_by_assignment(vector<vector<int>> problem, vector<int> variables_assigment) {
    int number_of_clauses_satisfied = 0;
    for (const auto& clause : problem) {
        // Ελέγχει αν ο όρος ικανοποιείται από την τρέχουσα ανάθεση
        if (variables_assigment[abs(clause[0]) - 1] * clause[0] > 0 ||
            variables_assigment[abs(clause[1]) - 1] * clause[1] > 0 ||
            variables_assigment[abs(clause[2]) - 1] * clause[2] > 0) {
            number_of_clauses_satisfied++;  // Αύξηση του μετρητή για κάθε ικανοποιημένο όρο
        }
    }
    return number_of_clauses_satisfied;
}

// Υπολογίζει τον αριθμό των ικανοποιημένων όρων για κάθε πιθανό flip μεταβλητής
vector<int> update_satisfied_clauses_num_per_flip(vector<vector<int>> problem, vector<int> variables_assigment) {
    vector<int> satisfied_clauses_per_flip(variables_assigment.size(), 0);
    for (int i = 0; i < variables_assigment.size(); i++) {
        // Flip προσωρινά τη μεταβλητή
        variables_assigment[i] = -variables_assigment[i];
        // Υπολογισμός των όρων που ικανοποιούνται μετά το flip
        satisfied_clauses_per_flip[i] = number_of_clauses_satisfied_by_assignment(problem, variables_assigment);
        // Επαναφορά της μεταβλητής στην αρχική της τιμή
        variables_assigment[i] = -variables_assigment[i];
    }
    return satisfied_clauses_per_flip;
}

// Επιλέγει τη μεταβλητή για flip που μεγιστοποιεί τον αριθμό των ικανοποιημένων όρων
int choose_flip_maximum_satisfied_clauses(vector<int> satisfied_clauses_per_flip) {
    int max_satisfied_clauses = 0;
    int flip_index = 0;
    for (int i = 0; i < satisfied_clauses_per_flip.size(); i++) {
        if (satisfied_clauses_per_flip[i] > max_satisfied_clauses) {
            max_satisfied_clauses = satisfied_clauses_per_flip[i];
            flip_index = i;  // Καταγραφή του δείκτη της μεταβλητής που θα γίνει flip
        }
    }
    return flip_index;
}

// Επιλέγει το καλύτερο flip μέσα σε έναν συγκεκριμένο όρο
int choose_best_flip_in_clause(vector<int> clause, vector<int> satisfied_clauses_per_flip) {
    int max_satisfied_clauses = 0;
    int flip_index = 0;
    for (int i = 0; i < clause.size(); i++) {
        // Ελέγχει αν το flip της μεταβλητής μεγιστοποιεί τον αριθμό των ικανοποιημένων όρων
        if (satisfied_clauses_per_flip[abs(clause[i]) - 1] > max_satisfied_clauses) {
            max_satisfied_clauses = satisfied_clauses_per_flip[abs(clause[i]) - 1];
            flip_index = abs(clause[i]) - 1;  // Καταγραφή του δείκτη της μεταβλητής που θα γίνει flip
        }
    }
    return flip_index;
}

// Δημιουργεί μια αρχική ανάθεση μεταβλητών με ημι-άπληστη μέθοδο
vector<int> semi_greedy_initial_assignment(vector<vector<int>> problem, int variables_num, double a) {
    vector<int> variables_assigment(variables_num, 0);

    // Αρχικοποίηση με τυχαία ανάθεση
    variables_assigment = assign_random_values(variables_num);

    // Ρύθμιση της ανάθεσης με βάση το επίπεδο άπληστης συμπεριφοράς 'a'
    for (int i = 0; i < variables_num; i++) {
        if ((static_cast<double>(rand()) / RAND_MAX) < a) {
            // Flip της μεταβλητής αν μειώνει τον αριθμό των μη ικανοποιημένων όρων
            vector<int> temp_assignment = variables_assigment;
            temp_assignment[i] = -temp_assignment[i];
            int current_cost = number_of_clauses_satisfied_by_assignment(problem, variables_assigment);
            int new_cost = number_of_clauses_satisfied_by_assignment(problem, temp_assignment);
            if (new_cost > current_cost) {
                variables_assigment[i] = temp_assignment[i];  // Ενημέρωση της μεταβλητής αν βελτιώνει το κόστος
            }
        }
        // Διατήρηση της τυχαίας ανάθεσης αν δεν γίνει το flip
    }
    return variables_assigment;
}

// Επιστρέφει μια λίστα με τους μη ικανοποιημένους όρους για την τρέχουσα ανάθεση
vector<int> find_unsatisfied_clauses(vector<vector<int>> problem, vector<int> variables_assigment) {
    vector<int> unsatisfied_clauses;
    for (int i = 0; i < problem.size(); i++) {
        bool satisfied = false;
        // Έλεγχος αν ο όρος i ικανοποιείται από την τρέχουσα ανάθεση
        for (int j = 0; j < 3; j++) {
            if (variables_assigment[abs(problem[i][j]) - 1] * problem[i][j] > 0) {
                satisfied = true;
                break;
            }
        }
        if (!satisfied) {
            unsatisfied_clauses.push_back(i);  // Προσθήκη του όρου στη λίστα μη ικανοποιημένων όρων
        }
    }
    return unsatisfied_clauses;
}
