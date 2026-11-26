// Gregaire.cpp
#include "Gregaire.h"
#include "Bestiole.h"
#include <cmath>

void Gregaire::agir( Bestiole & b, const std::vector<Bestiole*> & proches, Bestiole * )
{
   if ( proches.empty() ) return;

   double sx = 0., sy = 0.;
   for ( Bestiole * o : proches ) {
      sx += std::cos( o->getOrientation() );
      sy += std::sin( o->getOrientation() );
   }
   b.setOrientation( std::atan2( sy, sx ) );   // moyenne de vecteurs unitaires
}