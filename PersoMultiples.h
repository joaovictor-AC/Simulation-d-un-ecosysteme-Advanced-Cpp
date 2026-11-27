// PersoMultiples.h
#ifndef _PersoMultiples_H_
#define _PersoMultiples_H_

#include <vector>
#include "Comportement.h"

class PersoMultiples : public Comportement
{
private:
   Comportement* courant;
   int compteur;
   double vitesseNormale;
   bool init;
   void changer(Bestiole& b);

public :
   PersoMultiples();
   PersoMultiples(const PersoMultiples& autre);
   ~PersoMultiples() override;
   PersoMultiples& operator=(const PersoMultiples&) = delete;

   void agir( Bestiole & b,
              const std::vector<Bestiole*> & proches,
              Bestiole * plusProche ) override;

   Comportement * clone() const override { return new PersoMultiples( *this ); }
   Couleur getCouleur() const override { return Couleur{ 150, 0, 200 }; }
};

#endif