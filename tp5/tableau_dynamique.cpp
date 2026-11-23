#include <cassert>
#include <cstddef>
#include <print>

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

int main()
{
    TableauDynamique notes;
    for (int i{0}; i < 10; ++i) {
        ajouter(notes, 10.0 + static_cast<double>(i));
    }
    std::println("taille {:>2}, capacité {:>2}", notes.taille, notes.capacite);
    std::println("premier élément : {:.2f}", element(notes, 0));
    liberer(notes);
    return 0;
}
