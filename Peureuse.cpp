// Peureuse.cpp
#include "Peureuse.h"
#include "Bestiole.h"
#include <cmath>

void Peureuse::agir( Bestiole & b, const std::vector<Bestiole*> & proches, Bestiole * )
{
   if ( !init ) { vitesseCroisiere = b.getVitesse(); init = true; }

   if ( toursFuite > 0 ) {                                   // en fuite
      if ( --toursFuite == 0 )
         b.setVitesse( vitesseCroisiere );                   // retour à la croisière
   }
   else if ( static_cast<int>( proches.size() ) > Bestiole::NB_MAX ) { // déclenchement
      b.setOrientation( b.getOrientation() + M_PI );
      b.setVitesse( vitesseCroisiere * Bestiole::FACTEUR_FUITE );
      toursFuite = Bestiole::DUREE_FUITE;
   }
}