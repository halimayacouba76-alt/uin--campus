#pragma once
#include "uincampus/regles.hpp"
#include <span>

namespace uin {

struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    double ecartType{};
};

[[nodiscard]] double somme(std::span<const double> valeurs);

/// @pre notes n'est pas vide
[[nodiscard]] double moyenne(std::span<const double> notes);

/// @pre notes n'est pas vide, même taille que coefficients, somme des coefficients > 0
[[nodiscard]] double moyenne(std::span<const double> notes,
                             std::span<const double> coefficients);

/// @pre notes n'est pas vide
[[nodiscard]] Statistiques calculerStatistiques(std::span<const double> notes);

[[nodiscard]] int compterValidees(std::span<const double> notes,
                            double seuil = seuilValidation);

[[nodiscard]] double arrondir(double valeur, int decimales = 2);

} // namespace uin

