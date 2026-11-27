// Prevoyante.cpp
#include "Prevoyante.h"
#include "Bestiole.h"
#include <cmath>

void Prevoyante::agir( Bestiole & b, const std::vector<Bestiole*> & proches, Bestiole * )
{
   // direction de b (vecteur unitaire, y vers le bas)
   double bx =  std::cos( b.getOrientation() );
   double by = -std::sin( b.getOrientation() );

   for ( Bestiole * o : proches ) {

<<<<<<< HEAD
      for ( int k = 1; k <= Bestiole::HORIZON; ++k ) {
         // positions dans k pas (repère image : y vers le bas)
         double mx = b.getX() + std::cos( b.getOrientation() ) * b.getVitesseEffective() * k;
         double my = b.getY() - std::sin( b.getOrientation() ) * b.getVitesseEffective() * k;
         double ox = o->getX() + std::cos( o->getOrientation() ) * o->getVitesseEffective() * k;
         double oy = o->getY() - std::sin( o->getOrientation() ) * o->getVitesseEffective() * k;
=======
      // direction de la voisine
      double ox =  std::cos( o->getOrientation() );
      double oy = -std::sin( o->getOrientation() );
>>>>>>> 5db0574305a8ec92db2f0d0e7d17e2f9a476114a

      // trajectoires parallèles : elles ne se croisent pas
      double det = -bx * oy + ox * by;
      if ( std::fabs( det ) < 1e-6 ) continue;

      // vecteur de b vers la voisine
      double rx = o->getX() - b.getX();
      double ry = o->getY() - b.getY();

      // point de croisement : b + t*dirB = o + s*dirO
      double t = ( -rx * oy + ox * ry ) / det;
      double s = ( bx * ry - by * rx ) / det;

      // les deux trajectoires croisent le même point DEVANT chacune
      if ( t > 0. && s > 0. ) {
         double cote = bx * ry - by * rx;       // côté où se trouve la voisine
         if ( cote > 0. )
            b.setOrientation( b.getOrientation() + M_PI / 4. );
         else
            b.setOrientation( b.getOrientation() - M_PI / 4. );
         return;                                 // un ajustement par pas
      }
   }
}