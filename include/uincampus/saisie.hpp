#ifndef UINCAMPUS_SAISIE_HPP
#define UINCAMPUS_SAISIE_HPP

#include <string>
#include <string_view>

namespace uin {

std::string lireTexte(std::string_view invite);
int lireEntier(std::string_view invite, int min, int max);
double lireNote(std::string_view invite);

} // namespace uin

#endif // UINCAMPUS_SAISIE_HPP
