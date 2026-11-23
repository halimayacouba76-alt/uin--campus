#ifndef UINCAMPUS_REGLES_HPP
#define UINCAMPUS_REGLES_HPP
#include <array>

#include <string_view>

namespace uin {

enum class Mention {
    Ajourne,
    Passable,
    AssezBien,
    Bien,
    TresBien
};

inline constexpr double seuilValidation = 10.0;
/// Seuils d'accès aux mentions Passable, Assez bien, Bien et Très bien.
inline constexpr std::array seuilsMentions{10.0, 12.0, 14.0, 16.0};
static_assert(seuilsMentions.size() == 4, "Un seuil par mention au-dessus d'Ajourné");
static_assert(seuilsMentions[0] == seuilValidation,
              "La mention Passable commence au seuil de validation");

Mention mentionPour(double moyenne);
std::string_view libelle(Mention mention);

} // namespace uin

#endif // UINCAMPUS_REGLES_HPP
