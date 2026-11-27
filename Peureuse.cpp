// Peureuse.cpp
#include "Peureuse.h"
#include "Bestiole.h"
#include <cmath>

void Peureuse::agir(
    Bestiole &b,
    const std::vector<Bestiole *> &proches,
    Bestiole *)
{
   if (toursFuite > 0)
   {
      --toursFuite;

      if (toursFuite == 0)
         b.setVitesse(b.getVitesseCroisiere());

      return;
   }

   if (static_cast<int>(proches.size()) > Bestiole::NB_MAX)
   {
      b.setOrientation(b.getOrientation() + M_PI);

      b.setVitesse(
          b.getVitesseCroisiere() * Bestiole::FACTEUR_FUITE);

      toursFuite = Bestiole::DUREE_FUITE;
   }
}