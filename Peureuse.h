// Peureuse.h
#ifndef _PEUREUSE_H_
#define _PEUREUSE_H_

#include <vector>
#include "Comportement.h"

class Peureuse : public Comportement
{
private:
   bool init = false;
   double vitesseCroisiere = 0.;
   int toursFuite = 0;

public :
   void agir( Bestiole & b,
              const std::vector<Bestiole*> & proches,
              Bestiole * plusProche ) override;

   Comportement * clone() const override { return new Peureuse( *this ); }
   Couleur getCouleur() const override { return Couleur{ 0, 0, 220 }; }
};

#endif