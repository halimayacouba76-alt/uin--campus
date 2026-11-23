#ifndef UINCAMPUS_REGLES_HPP
#define UINCAMPUS_REGLES_HPP

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

Mention mentionPour(double moyenne);
std::string_view libelle(Mention mention);

} // namespace uin

#endif // UINCAMPUS_REGLES_HPP
