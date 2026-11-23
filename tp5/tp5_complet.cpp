#include <cassert>
#include <cstddef>
#include <print>
#include <vector>

struct TableauDynamique {
    double* donnees{nullptr};
    std::size_t taille{0};
    std::size_t capacite{0};
};

void ajouter(TableauDynamique& t, double valeur)
{
    if (t.taille == t.capacite) {
        const std::size_t nouvelleCapacite = (t.capacite == 0) ? 4 : t.capacite * 2;
        double* nouveau = new double[nouvelleCapacite];
        for (std::size_t i{0}; i < t.taille; ++i) {
            nouveau[i] = t.donnees[i];
        }
        delete[] t.donnees;
        t.donnees = nouveau;
        t.capacite = nouvelleCapacite;
    }
    t.donnees[t.taille] = valeur;
    ++t.taille;
}

void liberer(TableauDynamique& t)
{
    delete[] t.donnees;
    t.donnees = nullptr;
    t.taille = 0;
    t.capacite = 0;
}

[[nodiscard]] double& element(TableauDynamique& t, std::size_t i)
{
    assert(i < t.taille && "element(): indice hors limites");
    return t.donnees[i];
}

void executerPartieA()
{
    std::println("=== Partie A : TableauDynamique ===");
    TableauDynamique notes;
    for (int i{0}; i < 10; ++i) {
        ajouter(notes, 10.0 + static_cast<double>(i));
    }
    std::println("taille {:>2}, capacité {:>2}", notes.taille, notes.capacite);
    std::println("premier élément : {:.2f}", element(notes, 0));
    liberer(notes);
}

void executerPartieB()
{
    std::println("\n=== Partie B : Piège de la copie ===");
    TableauDynamique notes;
    for (int i{0}; i < 10; ++i) {
        ajouter(notes, 10.0 + static_cast<double>(i));
    }

    TableauDynamique copie = notes;
    liberer(copie);
    // Décommente la ligne suivante puis compile avec -fsanitize=address,undefined
    // pour observer l'erreur "attempting double-free" :
    // liberer(notes);
    notes.donnees = nullptr;
    notes.taille = 0;
    notes.capacite = 0;
    std::println("copie superficielle testée (décommenter liberer(notes) pour voir le double-free)");
}

void executerPartieC()
{
    std::println("\n=== Partie C : std::vector (RAII) ===");
    std::vector<double> notes;
    for (int i{0}; i < 10; ++i) {
        notes.push_back(10.0 + static_cast<double>(i));
    }
    std::println("taille {:>2}, capacité {:>2}", notes.size(), notes.capacity());

    std::vector<double> copie = notes;
    std::println("taille copie {:>2}, capacité copie {:>2}", copie.size(), copie.capacity());
}

int main()
{
    executerPartieA();
    executerPartieB();
    executerPartieC();
    return 0;
}
