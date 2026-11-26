// Nageoires.h
#ifndef _NAGEOIRES_H_
#define _NAGEOIRES_H_
class Nageoires
{
public :
   double nu;      // multiplie la vitesse, dans [1 ; nuMax]
   Nageoires() : nu( 1. ) {}
   explicit Nageoires( double n ) : nu( n ) {}
};
#endif