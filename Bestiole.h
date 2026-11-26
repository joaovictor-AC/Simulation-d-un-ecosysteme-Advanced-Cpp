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
   double            taille;          
 
   int               age;             
   int               ageLimite;       
   bool              vivante;
 
   T                 couleur[ 3 ];    // vector normal, el puntero daba problemas de compilacion
 
private :
   void bouge( int xLim, int yLim );
 
public :
   Bestiole( void );
 
   Bestiole cloner( void ) const;    // copia una bestiole pero cambia id
 
   void action( Milieu & monMilieu );
   void draw( UImg & support );
 
   bool jeTeVois( const Bestiole & b ) const;
 
   void initCoords( int xLim, int yLim );
 
   void vieillir( void ) { ++age; }                                  // acción: solo envejece
   bool estTropVieille( void ) const { return age >= ageLimite; }    // pregunta: no modifica nada
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
 
