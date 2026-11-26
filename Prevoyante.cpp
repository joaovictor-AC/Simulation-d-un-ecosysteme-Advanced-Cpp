// Prevoyante.cpp
#include "Prevoyante.h"
#include "Bestiole.h"
#include <cmath>

void Prevoyante::agir( Bestiole & b, const std::vector<Bestiole*> & proches, Bestiole * )
{
   for ( Bestiole * o : proches ) {
      double seuil = ( b.getTaille() + o->getTaille() ) / 2.;

      for ( int k = 1; k <= HORIZON; ++k ) {
         // positions dans k pas (repère image : y vers le bas)
         double mx = b.getX() + std::cos( b.getOrientation() ) * b.getVitesse() * k;
         double my = b.getY() - std::sin( b.getOrientation() ) * b.getVitesse() * k;
         double ox = o->getX() + std::cos( o->getOrientation() ) * o->getVitesse() * k;
         double oy = o->getY() - std::sin( o->getOrientation() ) * o->getVitesse() * k;

         double d = std::sqrt( (mx-ox)*(mx-ox) + (my-oy)*(my-oy) );
         if ( d < seuil ) {                                   // collision prévue
            b.setOrientation( b.getOrientation() + M_PI/2. );
            return;                                           // une seule déviation par pas
         }
      }
   }
}