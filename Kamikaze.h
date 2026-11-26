// Kamikaze.h
#ifndef _KAMIKAZE_H_
#define _KAMIKAZE_H_

#include <vector>
#include "Comportement.h"

class Kamikaze : public Comportement
{
public :
   void agir( Bestiole & b,
              const std::vector<Bestiole*> & proches,
              Bestiole * plusProche ) override;

   Comportement * clone() const override { return new Kamikaze( *this ); }
   Couleur getCouleur() const override { return Couleur{255, 0, 0 }; }
};

#endif