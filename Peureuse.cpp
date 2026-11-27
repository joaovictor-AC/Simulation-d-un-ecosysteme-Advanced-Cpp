// Peureuse.cpp
#include "Peureuse.h"
#include "Bestiole.h"
#include <cmath>

void Peureuse::agir( Bestiole & b, const std::vector<Bestiole*> & proches, Bestiole * plusProche )
{
<<<<<<< HEAD
   if ( !init ) { vitesseCroisiere = b.getVitesse(); init = true; }

   if ( toursFuite > 0 ) {                                   // en fuite
      if ( --toursFuite == 0 )
         b.setVitesse( vitesseCroisiere );                   // retour à la croisière
   }
   else if ( static_cast<int>( proches.size() ) > Bestiole::NB_MAX ) { // déclenchement
      b.setOrientation( b.getOrientation() + M_PI );
      b.setVitesse( vitesseCroisiere * Bestiole::FACTEUR_FUITE );
      toursFuite = Bestiole::DUREE_FUITE;
=======
   if ( static_cast<int>( proches.size() ) > NB_MAX ) {
      b.setOrientation( b.getOrientation() + M_PI );   // direction opposée
      b.setVitesseEffective( MAX_VITESSE );                  // vive allure
>>>>>>> 5db0574305a8ec92db2f0d0e7d17e2f9a476114a
   }
}