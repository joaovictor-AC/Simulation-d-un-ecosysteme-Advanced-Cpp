#include "Bestiole.h"
 
#include "Milieu.h"
 
#include <cstdlib>
#include <cmath>
 
 
const double      Bestiole::MAX_VITESSE = 10.;
const double      Bestiole::LIMITE_VUE = 30.;
const double      Bestiole::TAILLE_MIN = 6.;
const double      Bestiole::TAILLE_MAX = 12.;
const int         Bestiole::AGE_MIN = 500;
const int         Bestiole::AGE_MAX = 2000;
 
int               Bestiole::next = 0;
 
 
namespace
{
   // Réel aléatoire dans [a ; b]
   double aleatoire( double a, double b )
   {
      return a + static_cast<double>( rand() )/RAND_MAX*( b - a );
   }
}
 
 
Bestiole::Bestiole( void )
{
 
   identite = ++next;
 
   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = aleatoire( 0., 2.*M_PI );
   vitesse = aleatoire( 0., MAX_VITESSE );
   taille = aleatoire( TAILLE_MIN, TAILLE_MAX );
 
   age = 0;
   ageLimite = AGE_MIN + rand() % ( AGE_MAX - AGE_MIN + 1 );
   vivante = true;
 
   couleur[ 0 ] = static_cast<T>( aleatoire( 0., 230. ) );
   couleur[ 1 ] = static_cast<T>( aleatoire( 0., 230. ) );
   couleur[ 2 ] = static_cast<T>( aleatoire( 0., 230. ) );
 
}
 
 
// Clonage : tout est copié (position, direction, âge...), sauf l'identité.
Bestiole Bestiole::cloner( void ) const
{
 
   Bestiole    copie( *this );       // copie exacte (constructeur de copie par défaut)
 
   copie.identite = ++next;
   copie.cumulX = copie.cumulY = 0.;
   return copie;
 
}
 
 
void Bestiole::initCoords( int xLim, int yLim )
{
 
   x = rand() % xLim;
   y = rand() % yLim;
 
}
 
 
void Bestiole::bouge( int xLim, int yLim )
{
 
   double         nx, ny;
   double         dx = cos( orientation )*vitesse;
   double         dy = -sin( orientation )*vitesse;
   int            cx, cy;
 
 
   cx = static_cast<int>( cumulX ); cumulX -= cx;
   cy = static_cast<int>( cumulY ); cumulY -= cy;
 
   nx = x + dx + cx;
   ny = y + dy + cy;
 
   if ( (nx < 0) || (nx > xLim - 1) ) {
      orientation = M_PI - orientation;
      cumulX = 0.;
   }
   else {
      x = static_cast<int>( nx );
      cumulX += nx - x;
   }
 
   if ( (ny < 0) || (ny > yLim - 1) ) {
      orientation = -orientation;
      cumulY = 0.;
   }
   else {
      y = static_cast<int>( ny );
      cumulY += ny - y;
   }
 
}
 
 
void Bestiole::action( Milieu & monMilieu )
{
 
   bouge( monMilieu.getWidth(), monMilieu.getHeight() );
 
}
 
 
bool Bestiole::vieillir( void )
{
 
   if ( !vivante ) return false;
 
   ++age;
   if ( age >= ageLimite ) {
      vivante = false;
      return true;
   }
   return false;
 
}
 
 
void Bestiole::rebondir( void )
{
 
   orientation = std::fmod( orientation + M_PI, 2.*M_PI );
 
}
 
 
void Bestiole::draw( UImg & support )
{
 
   double         xt = x + cos( orientation )*taille/2.1;
   double         yt = y - sin( orientation )*taille/2.1;
 
 
   support.draw_ellipse( x, y, taille, taille/5., -orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, taille/2., couleur );
 
}
 
 
bool operator==( const Bestiole & b1, const Bestiole & b2 )
{
 
   return ( b1.identite == b2.identite );
 
}
 
 
bool Bestiole::jeTeVois( const Bestiole & b ) const
{
 
   double         dist;
 
 
   dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   return ( dist <= LIMITE_VUE );
 
}
 
