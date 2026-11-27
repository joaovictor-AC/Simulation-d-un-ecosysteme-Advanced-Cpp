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

      // direction de la voisine
      double ox =  std::cos( o->getOrientation() );
      double oy = -std::sin( o->getOrientation() );

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