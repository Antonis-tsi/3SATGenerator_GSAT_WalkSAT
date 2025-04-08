#include "solvers_help_functions.h"
#include <vector>
#include <iostream>

using namespace std;

///ΝΙΚΟΟΟΟΟΟΟΟΟΟΟΟ!!!!!!!!
//Η ΠΡΟΗΓΟΥΜΕΝΗ ΔΕΝ ΕΚΑΝΕ ΕΛΕΓΧΟ ΠΡΙΝ ΔΙΑΛΕΞΕΙ ΤΟ ΤΥΧΑΙΟ ΦΛΙΠ (ΠΡΙΝ ΤΟ RANDOM WWALK) ΑΝ ΟΔΗΓΟΥΣΕ ΣΕ ΠΕΡΙΣΣΟΤΕΡΟΥΣ ΙΚΑΝΟΠΟΙΗΜΕΝΟΥΣ ΟΡΟΥΣ ΑΠΟ ΤΗΝ ΠΡΟΗΓΟΥΜΕΝΗ ΚΑΤΑΣΤΑΣΗ
//ΕΙΝΑΙ ΟΛΟΙΔΙΑ ΜΕ ΤΗΝ WALKSAT ΠΟΥ ΕΙΧΕΣ ΑΠΛΑ ΑΛΛΑΖΕΙ Η ΡΑΝΤΟΜ ΑΡΧΙΚΟΠΟΙΗΣΗ ME TH ΣΥΝΑΡΤΗΣΗ, ΦΑΝΤΑΖΟΜΑΙ ΕΤΣΙ ΠΡΕΠΕΙ ΝΑ ΕΙΝΑΙ ΑΛΛΑ ΔΕΝ ΕΙΜΑΙ ΣΙΓΟΥΡΟΣ
//ΔΕΝ ΞΕΡΩ ΑΝ ΤΡΕΧΕΙ ΤΣΕΚΑΡΕ ΤΟ
//ΑΝ ΑΦΗΣΕΙΣ ΤΗ ΠΡΟΗΓΟΥΜΕΝΗ ΑΛΛΑΞΕ ΤΟΥΛΑΧΙΣΤΟΝ ΤΑ ΑΓΓΛΙΚΑ ΣΧΟΛΙΑ ΓΙΑΤΙ ΠΑΙΖΕΙ ΝΑ ΧΡΕΩΘΟΥΜΕ
//<3<3<3<3<3<3<3<3

vector<int> walksat_semi_greedy(vector<vector<int>> problem, int maxflips, int maxtries, double propability, int variables_num, double a) {
    vector<int> variables_assigment(variables_num, 0);
    int current_satisfied_clauses = 0;
    int clauses_num = problem.size();
    vector<int> satisfied_clauses_per_flip(variables_num, 0);  // Αριθμός ικανοποιημένων όρων ανά flip
    int rand_clause_index = 0;
    int literal_index_in_clause = 0;
    vector<int> unsatisfied_clauses;
    vector<int> potential_variables_flip;  // Λίστα με πιθανές μεταβλητές προς flip
    vector<int> random_clause(3);  // Τυχαίος μη ικανοποιημένος όρος
    vector<int> best_variables_assigment(variables_num, 0);
    int best_cost = 0;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < maxtries; i++) {
        // Χρήση semi-greedy αρχικής ανάθεσης
        variables_assigment = semi_greedy_initial_assignment(problem, variables_num, a);

        for (int j = 0; j < maxflips; j++) {
            current_satisfied_clauses = number_of_clauses_satisfied_by_assignment(problem, variables_assigment);

            // Αν βρεθεί καλύτερη ανάθεση, ενημερώνεται η καλύτερη ανάθεση και το κόστος
            if (current_satisfied_clauses > best_cost) {
                best_variables_assigment = variables_assigment;
                best_cost = current_satisfied_clauses;
            }

            // Αν όλοι οι όροι ικανοποιούνται, επιστρέφει τη λύση
            if (current_satisfied_clauses == clauses_num) {
                return variables_assigment;
            } else {
                // Εύρεση μη ικανοποιημένων όρων
                unsatisfied_clauses = find_unsatisfied_clauses(problem, variables_assigment);

                // Επιλογή τυχαίου μη ικανοποιημένου όρου
                rand_clause_index = rand() % unsatisfied_clauses.size();
                random_clause = problem[unsatisfied_clauses[rand_clause_index]];

                // Υπολογισμός των ικανοποιημένων όρων ανά flip
                satisfied_clauses_per_flip = update_satisfied_clauses_num_per_flip(problem, variables_assigment);

                // Εύρεση πιθανών μεταβλητών για flip που αυξάνουν τον αριθμό των ικανοποιημένων όρων
                for (int k = 0; k < 3; k++) {
                    if (satisfied_clauses_per_flip[abs(random_clause[k]) - 1] > current_satisfied_clauses) {
                        literal_index_in_clause = abs(random_clause[k]) - 1;
                        potential_variables_flip.push_back(literal_index_in_clause);
                    }
                }

                // Αν υπάρχουν πιθανές μεταβλητές για flip, επιλέγεται μία τυχαία
                if (potential_variables_flip.size() > 0) {
                    literal_index_in_clause = potential_variables_flip[rand() % potential_variables_flip.size()];
                    potential_variables_flip.clear();  // Εκκαθάριση της λίστας
                } else {
                    // Απόφαση για τυχαίο περπάτημα ή επιλογή καλύτερης μεταβλητής για flip
                    bool do_random_walk = (static_cast<double>(rand()) / RAND_MAX < propability);
                    if (do_random_walk) {
                        // Επιλογή τυχαίου literal από τον όρο
                        literal_index_in_clause = abs(random_clause[rand() % 3]) - 1;
                    } else {
                        // Επιλογή της καλύτερης μεταβλητής για flip με βάση την ικανοποίηση όρων
                        literal_index_in_clause = choose_best_flip_in_clause(random_clause, satisfied_clauses_per_flip);
                    }
                }

                // Εκτέλεση flip στη μεταβλητή που επιλέχθηκε
                variables_assigment[literal_index_in_clause] = -variables_assigment[literal_index_in_clause];
            }
        }
    }

    // Εκτύπωση της καλύτερης ανάθεσης που βρέθηκε αν δεν βρεθεί πλήρης λύση
    cout << "Best semi-greedy walksat assigment found: ";
    for (int val : best_variables_assigment) {
        cout << val << " ";
    }
    cout << "best_cost: " << clauses_num - best_cost << endl;

    return {};  // Επιστροφή κενού vector αν δεν βρεθεί λύση
}
