#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <limits>
#include <print>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace {

struct EntierLu {
    bool valide{false};
    int valeur{0};
};

struct ReelLu {
    bool valide{false};
    double valeur{0.0};
};

[[nodiscard]] std::string lireLigne(std::string_view invite)
{
    std::print("{}", invite);
    std::string ligne;
    if (!std::getline(std::cin, ligne)) {
        return {};
    }
    return ligne;
}

[[nodiscard]] EntierLu versEntier(const std::string& texte)
{
    std::istringstream flux{texte};
    int valeur{};
    char reste{};
    const bool valide = static_cast<bool>(flux >> valeur) && !(flux >> reste);
    return EntierLu{.valide = valide, .valeur = valeur};
}

[[nodiscard]] ReelLu versReel(std::string texte)
{
    for (char& c : texte) {
        if (c == ',') {
            c = '.';
        }
    }
    std::istringstream flux{texte};
    double valeur{};
    char reste{};
    const bool valide = static_cast<bool>(flux >> valeur) && !(flux >> reste);
    return ReelLu{.valide = valide, .valeur = valeur};
}

} // namespace

[[nodiscard]] int lireEntier(std::string_view invite, int min, int max)
{
    while (std::cin) {
        const auto [valide, valeur] = versEntier(lireLigne(invite));
        if (!valide) {
            std::println("Saisie invalide : entrez un nombre entier.");
        } else if (valeur < min || valeur > max) {
            std::println("La valeur doit être comprise entre {} et {}.", min, max);
        } else {
            return valeur;
        }
    }
    return min;
}

[[nodiscard]] double lireNote(std::string_view invite)
{
    constexpr double noteMin{0.0};
    constexpr double noteMax{20.0};

    while (std::cin) {
        const auto [valide, note] = versReel(lireLigne(invite));
        if (!valide) {
            std::println("Saisie invalide : entrez un nombre (ex. 12.5 ou 12,5).");
        } else if (note < noteMin || note > noteMax) {
            std::println("La note doit être comprise entre {:.1f} et {:.1f}.", noteMin, noteMax);
        } else {
            return note;
        }
    }
    return noteMin;
}

namespace carnet {

enum class Ordre {
    Croissant,
    Decroissant,
};

struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    int nbValidees{};
};

/// @pre notes n'est pas vide
[[nodiscard]] Statistiques calculerStatistiques(const std::vector<double>& notes)
{
    assert(!notes.empty() && "calculerStatistiques(): la liste de notes est vide");
    const auto [mini, maxi] = std::ranges::minmax(notes);
    double somme{0.0};
    int validees{0};
    for (const double n : notes) {
        somme += n;
        if (n >= 10.0) {
            ++validees;
        }
    }
    return Statistiques{
        .minimum = mini,
        .maximum = maxi,
        .moyenne = somme / static_cast<double>(notes.size()),
        .nbValidees = validees,
    };
}

void appliquerBonus(std::vector<double>& notes, double bonus)
{
    std::ranges::for_each(notes, [bonus](double& n) {
        n = std::clamp(n + bonus, 0.0, 20.0);
    });
}

void trier(std::vector<double>& notes, Ordre ordre)
{
    if (ordre == Ordre::Croissant) {
        std::ranges::sort(notes, [](double a, double b) { return a < b; });
    } else {
        std::ranges::sort(notes, [](double a, double b) { return a > b; });
    }
}

void afficherNotes(const std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note enregistrée.");
        return;
    }
    for (std::size_t i{0}; i < notes.size(); ++i) {
        std::println("{:>3}. {:6.2f}", i + 1, notes[i]);
    }
}

void ajouter(std::vector<double>& notes)
{
    notes.push_back(lireNote("Note à ajouter : "));
}

void modifier(std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note à modifier.");
        return;
    }
    afficherNotes(notes);
    const int rang = lireEntier("Numéro de la note : ", 1, static_cast<int>(notes.size()));
    notes[static_cast<std::size_t>(rang - 1)] = lireNote("Nouvelle valeur : ");
}

void supprimer(std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note à supprimer.");
        return;
    }
    afficherNotes(notes);
    const int rang = lireEntier("Numéro de la note : ", 1, static_cast<int>(notes.size()));
    notes.erase(notes.begin() + (rang - 1));
}

void afficherStatistiques(const std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note enregistrée.");
        return;
    }
    const auto [mini, maxi, moyenne, validees] = calculerStatistiques(notes);
    std::println("Min : {:.2f} | Max : {:.2f} | Moyenne : {:.2f} | Validées : {}/{}",
                 mini, maxi, moyenne, validees, notes.size());
}

[[nodiscard]] int afficherMenu()
{
    std::println("\n=== Carnet de notes ===");
    std::println("1. Ajouter une note");
    std::println("2. Afficher les notes");
    std::println("3. Modifier une note");
    std::println("4. Supprimer une note");
    std::println("5. Trier les notes (croissant / décroissant)");
    std::println("6. Statistiques");
    std::println("7. Appliquer un bonus");
    std::println("0. Quitter");
    return lireEntier("Votre choix : ", 0, 7);
}

} // namespace carnet

int main()
{
    std::vector<double> notes;
    int choix{};
    do {
        choix = carnet::afficherMenu();
        switch (choix) {
        case 1:
            carnet::ajouter(notes);
            break;
        case 2:
            carnet::afficherNotes(notes);
            break;
        case 3:
            carnet::modifier(notes);
            break;
        case 4:
            carnet::supprimer(notes);
            break;
        case 5: {
            const int sens = lireEntier("1. Croissant  2. Décroissant : ", 1, 2);
            carnet::trier(notes, sens == 1 ? carnet::Ordre::Croissant : carnet::Ordre::Decroissant);
            break;
        }
        case 6:
            carnet::afficherStatistiques(notes);
            break;
        case 7:
            carnet::appliquerBonus(notes, lireNote("Bonus : "));
            break;
        case 0:
            std::println("Au revoir.");
            break;
        default:
            break;
        }
    } while (choix != 0);

    return 0;
}
