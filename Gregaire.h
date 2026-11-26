// Gregaire.h
#ifndef _GREGAIRE_H_
#define _GREGAIRE_H_

#include <vector>
#include "Comportement.h"

class Gregaire : public Comportement
{
public :
   void agir( Bestiole & b,
              const std::vector<Bestiole*> & proches,
              Bestiole * plusProche ) override;

   Comportement * clone() const override { return new Gregaire( *this ); }
   Couleur getCouleur() const override { return Couleur{ 0, 160, 0 }; }
};

#endif