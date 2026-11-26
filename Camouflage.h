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


#ifndef _EQUIPEMENTS_H_
#define _EQUIPEMENTS_H_

// Capteurs
struct Yeux
{
   double distance = 0.;   // portée
   double angle    = 0.;   // champ angulaire total (radians)
   double gamma    = 0.;   // capacité de détection [0 ; 1]
};

struct Oreilles
{
   double distance = 0.;
   double gamma    = 0.;
};

// Accessoires
struct Nageoires
{
   double nu = 0.;         // multiplicateur de vitesse
};

struct Carapace
{
   double omega = 0.;      // réduction de la probabilité de mort
   double eta   = 0.;      // ralentissement
};

struct Camouflage
{
   double psi = 0.;        // capacité de camouflage [0 ; 1]
};

#endif