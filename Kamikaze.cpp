// Kamikaze.cpp
#include "Kamikaze.h"
#include "Bestiole.h"
#include <cmath>

void Kamikaze::agir( Bestiole & b, const std::vector<Bestiole*> &, Bestiole * plusProche )
{
   if ( plusProche == nullptr ) return;

   double dx = plusProche->getX() - b.getX();
   double dy = plusProche->getY() - b.getY();
   b.setOrientation( std::atan2( -dy, dx ) );   // -dy : l'axe y de l'image pointe vers le bas
}