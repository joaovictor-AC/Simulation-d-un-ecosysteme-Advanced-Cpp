// Prevoyante.h
#ifndef _PREVOYANTE_H_
#define _PREVOYANTE_H_

#include <vector>
#include "Comportement.h"

class Prevoyante : public Comportement
{
public :
   void agir( Bestiole & b,
              const std::vector<Bestiole*> & proches,
              Bestiole * plusProche ) override;

   Comportement * clone() const override { return new Prevoyante( *this ); }
   Couleur getCouleur() const override { return Couleur{ 255, 140, 0 }; }
};

#endif