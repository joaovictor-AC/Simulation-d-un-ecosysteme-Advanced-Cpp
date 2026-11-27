// Camouflage.h
#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_
class Camouflage
{
public :
   double psi;     // capacité de camouflage, dans [psiMin ; psiMax] ⊂ [0 ; 1]
   Camouflage() : psi( 0. ) {} //constructeur par défault, il met le psi à 0
   explicit Camouflage( double p ) : psi( p ) {}
};
#endif
