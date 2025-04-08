#include "sat_generator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <algorithm>

using namespace std;

// Συνάρτηση για τη δημιουργία SAT προβλημάτων
vector<vector<vector<int>>> satgenerator(int variables_num, int clauses_num, double probability_negative, int problem_num) {
    vector<vector<vector<int>>> all_problems;  // Λίστα όλων των παραγόμενων προβλημάτων
    srand(static_cast<unsigned int>(time(nullptr)));  // Αρχικοποίηση της γεννήτριας τυχαίων αριθμών

    // Δημιουργία πολλαπλών προβλημάτων
    for (int p = 0; p < problem_num; p++) {
        vector<vector<int>> clauses;  // Λίστα με τους όρους του τρέχοντος προβλήματος
        set<string> visited;  // Σύνολο για την παρακολούθηση μοναδικών όρων

        // Δημιουργία όρων μέχρι να επιτευχθεί ο απαιτούμενος αριθμός (clauses_num)
        while (clauses.size() < clauses_num) {
            vector<int> clause(3);  // Δημιουργία όρου με 3 literals
            set<int> clause_literals;  // Σύνολο για την αποφυγή διπλότυπων literals στον όρο

            // Δημιουργία 3 διαφορετικών literals για τον όρο
            for (int j = 0; j < 3; j++) {
                int next_literal;
                do {
                    int sign = (static_cast<double>(rand()) / RAND_MAX < probability_negative) ? -1 : 1;  // Επιλογή θετικού ή αρνητικού πρόσημου με βάση την πιθανότητα
                    next_literal = sign * ((rand() % variables_num) + 1);  // Επιλογή μεταβλητής από 1 έως variables_num με τυχαίο πρόσημο
                } while (clause_literals.count(abs(next_literal)) > 0);  // Εξασφάλιση ότι το literal δεν έχει ήδη χρησιμοποιηθεί στον όρο

                clause[j] = next_literal;  // Προσθήκη του literal στον όρο
                clause_literals.insert(abs(next_literal));  // Προσθήκη της απόλυτης τιμής του literal στο σύνολο
            }

            sort(clause.begin(), clause.end());  // Ταξινόμηση του όρου για συνέπεια και αποφυγή διπλότυπων
            string clause_key = to_string(clause[0]) + " " + to_string(clause[1]) + " " + to_string(clause[2]);  // Δημιουργία μοναδικού κλειδιού για τον όρο

            // Αν ο όρος δεν έχει ήδη προστεθεί, προστίθεται στο πρόβλημα
            if (visited.find(clause_key) == visited.end()) {
                visited.insert(clause_key);  // Εισαγωγή του όρου στο σύνολο των μοναδικών όρων
                clauses.push_back(clause);  // Προσθήκη του όρου στη λίστα όρων
            }
        }

        all_problems.push_back(clauses);  // Προσθήκη του τρέχοντος προβλήματος στη λίστα όλων των προβλημάτων
    }

    return all_problems;  // Επιστροφή της λίστας με όλα τα παραγόμενα προβλήματα
}
