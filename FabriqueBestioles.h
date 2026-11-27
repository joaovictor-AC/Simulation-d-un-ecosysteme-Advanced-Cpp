#ifndef _FABRIQUE_BESTIOLES_H_
#define _FABRIQUE_BESTIOLES_H_
 
#include "Bestiole.h"
#include "distributionComportement.h"
 
class FabriqueBestioles
{
private :
   static const double        PROBA_EQUIPEMENT;   // proba d'avoir chaque capteur / accessoire
 
   DistributionComportement   distribution;       // pourcentages choisis dans le main
 
public :
   FabriqueBestioles( const DistributionComportement & d ) : distribution( d ) {}
 
   Bestiole creerBestiole( void ) const;
};
 
#endif
 