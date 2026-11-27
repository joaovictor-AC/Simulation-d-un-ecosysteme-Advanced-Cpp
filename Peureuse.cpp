// Peureuse.cpp
#include "Peureuse.h"
#include "Bestiole.h"
#include <cmath>

void Peureuse::agir( Bestiole & b, const std::vector<Bestiole*> & proches, Bestiole * plusProche )
{
   if ( static_cast<int>( proches.size() ) > NB_MAX ) {
      b.setOrientation( b.getOrientation() + M_PI );   // direction opposée
      b.setVitesseEffective( MAX_VITESSE );                  // vive allure
   }
}