#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_
 
 
#include "UImg.h"
 
#include <iostream>
 
using namespace std;
 
 
class Milieu;
 
 
class Bestiole
{
 
private :
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;
   static const double     TAILLE_MIN, TAILLE_MAX;
   static const int        AGE_MIN, AGE_MAX;
 
   static int              next;
 
private :
   int               identite;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   double            taille;          // demi grand axe de l'ellipse, propre à chaque bestiole
 
   int               age;             // en pas de simulation
   int               ageLimite;       // tiré au hasard à la naissance
   bool              vivante;
 
   T                 couleur[ 3 ];    // tableau simple : copié automatiquement, rien à libérer
 
private :
   void bouge( int xLim, int yLim );
 
public :
   Bestiole( void );
   // Copie, affectation et destruction générées par le compilateur :
   // copie EXACTE (même identité). Utilisées par std::vector quand il
   // déplace ses éléments. Pour un vrai clonage, utiliser cloner().
 
   Bestiole cloner( void ) const;    // copie conforme mais nouvelle identité
 
   void action( Milieu & monMilieu );
   void draw( UImg & support );
 
   bool jeTeVois( const Bestiole & b ) const;
 
   void initCoords( int xLim, int yLim );
 
   // ---- Cycle de vie ----
   bool vieillir( void );             // +1 pas ; vrai si elle vient de mourir de vieillesse
   void mourir( void ) { vivante = false; }
   bool estVivante( void ) const { return vivante; }
   void rebondir( void );             // repart dans la direction opposée
 
   // ---- Accesseurs utilisés par le Milieu ----
   int    getIdentite( void ) const { return identite; }
   int    getX( void ) const { return x; }
   int    getY( void ) const { return y; }
   double getOrientation( void ) const { return orientation; }
   double getVitesse( void ) const { return vitesse; }
   double getTaille( void ) const { return taille; }
   int    getAge( void ) const { return age; }
 
   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );
 
};
 
 
#endif
 
