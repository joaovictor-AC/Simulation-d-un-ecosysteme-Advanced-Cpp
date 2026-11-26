// Comportement.h
#ifndef _COMPORTEMENT_H_
#define _COMPORTEMENT_H_

#include <vector>
#include "Couleur.h"

class Bestiole;                      // déclaration anticipée

class Comportement
{
public :
   virtual ~Comportement() {}

   virtual void agir( Bestiole & b,
                      const std::vector<Bestiole*> & proches,
                      Bestiole * plusProche ) = 0;

   virtual Comportement * clone() const = 0;
   virtual Couleur getCouleur() const = 0;     // même type que dans les sous-classes
};

#endif