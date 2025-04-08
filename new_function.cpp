
int choose_flip_maximum_satisfied_clauses(const vector<int>& satisfied_clauses_per_flip) {
    int max_value = *max_element(satisfied_clauses_per_flip.begin(), satisfied_clauses_per_flip.end());
    vector<int> candidates;

    // Συλλογή όλων των δεικτών που έχουν την μέγιστη τιμή
    for (int i = 0; i < satisfied_clauses_per_flip.size(); i++) {
        if (satisfied_clauses_per_flip[i] == max_value) {
            candidates.push_back(i);
        }
    }

    // Επιλογή τυχαίου δείκτη από τους υποψηφίους
    int random_index = rand() % candidates.size();
    return candidates[random_index];
}
//ΝΙΚΟΟΟΟΟΟ!!!!!!!!!!!
//ΣΕ ΣΧΕΣΗ ΜΕ ΤΗ ΠΡΟΗΟΓΟΥΜΕΝΗ ΔΙΑΛΕΓΕΙ ΤΥΧΑΙΑ ΑΝΑΜΕΣΑ ΣΤΑ ΦΛΙΠΣ ΑΝ ΕΙΝΑΙ ΠΟΛΛΑ ΜΕ ΤΗΝ ΙΔΙΑ ΤΙΜΗ ΙΚΑΝΟΠΟΙΗΜΕΝΩΝ ΟΡΩΝ ΓΙΑ ΤΙΣ GSAT ΔΙΑΦΑΝΕΙΑ 8 
//ΒΑΛΤΗ ΜΕΣΑ ΣΤΟ SOLVERS HELP FUNCTIONS, ΔΕΝ ΞΕΡΩ ΑΝ ΤΡΕΧΕΙ ΤΣΕΚΑΡΕ ΤΟ
