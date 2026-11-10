cat << 'EOF' > src/statistiques.cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct StatistiquesNotes {
    double moyenne;
    double ecartType;
    double noteMin;
    double noteMax;
    int totalEtudiants;
    int echecs;
    int passable;
    int assezBien;
    int bien;
    int tresBien;
};

StatistiquesNotes calculerStatistiques(const vector<double>& notes) {
    StatistiquesNotes stats;
    stats.totalEtudiants = notes.size();
    
    if (stats.totalEtudiants == 0) {
        return {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }

    double somme = 0;
    stats.noteMin = notes[0];
    stats.noteMax = notes[0];
    stats.echecs = 0;
    stats.passable = 0;
    stats.assezBien = 0;
    stats.bien = 0;
    stats.tresBien = 0;

    for (double note : notes) {
        somme += note;
        if (note < stats.noteMin) stats.noteMin = note;
        if (note > stats.noteMax) stats.noteMax = note;

        if (note < 10.0) stats.echecs++;
        else if (note < 12.0) stats.passable++;
        else if (note < 14.0) stats.assezBien++;
        else if (note < 16.0) stats.bien++;
        else stats.tresBien++;
    }

    stats.moyenne = somme / stats.totalEtudiants;

    double sommeVariance = 0;
    for (double note : notes) {
        sommeVariance += pow(note - stats.moyenne, 2);
    }
    stats.ecartType = sqrt(sommeVariance / stats.totalEtudiants);

    return stats;
}

void afficherHistogramme(const StatistiquesNotes& stats) {
    cout << "\n--- HISTOGRAMME DES MENTIONS ---\n";
    auto barre = [](int count) { return string(count, '#'); };
    cout << "Echecs (<10)    : " << barre(stats.echecs) << " (" << stats.echecs << ")\n";
    cout << "Passable [10-12[: " << barre(stats.passable) << " (" << stats.passable << ")\n";
    cout << "Assez Bien [12-14[: " << barre(stats.assezBien) << " (" << stats.assezBien << ")\n";
    cout << "Bien [14-16]    : " << barre(stats.bien) << " (" << stats.bien << ")\n";
    cout << "Tres Bien (16+) : " << barre(stats.tresBien) << " (" << stats.tresBien << ")\n";
}

int main() {
    cout << "=== TP3 : STATISTIQUES D'UNE SERIE DE NOTES ===\n";
    int n;
    cout << "Entrez le nombre d'etudiants : ";
    if (!(cin >> n) || n <= 0) {
        cout << "Nombre invalide.\n";
        return 1;
    }

    vector<double> notes(n);
    for (int i = 0; i < n; ++i) {
        do {
            cout << "Note de l'etudiant " << (i + 1) << " (sur 20) : ";
            cin >> notes[i];
            if (notes[i] < 0 || notes[i] > 20) {
                cout << "Erreur : La note doit être comprise entre 0 et 20.\n";
            }
        } while (notes[i] < 0 || notes[i] > 20);
    }

    StatistiquesNotes stats = calculerStatistiques(notes);

    cout << fixed << setprecision(2);
    cout << "\n=== RÉSULTATS STATISTIQUES ===\n";
    cout << "Total d'étudiants : " << stats.totalEtudiants << "\n";
    cout << "Moyenne de la classe : " << stats.moyenne << " / 20\n";
    cout << "Écart-type : " << stats.ecartType << "\n";
    cout << "Note minimale : " << stats.noteMin << " / 20\n";
    cout << "Note maximale : " << stats.noteMax << " / 20\n";

    afficherHistogramme(stats);

    return 0;
}
EOF
