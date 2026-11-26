// Carapace.h
#ifndef _CARAPACE_H_
#define _CARAPACE_H_
class Carapace
{
public :
   double omega;   // divise la probabilité de mort, dans [1 ; omegaMax]
   double eta;     // divise la vitesse, dans [1 ; etaMax]
   Carapace() : omega( 1. ), eta( 1. ) {}
   Carapace( double o, double e ) : omega( o ), eta( e ) {}
};
#endif