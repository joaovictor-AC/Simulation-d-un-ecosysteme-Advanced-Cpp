// Peureuse.h
#ifndef _PEUREUSE_H_
#define _PEUREUSE_H_
#include "Comportement.h"

class Peureuse : public Comportement
{
private :
   static const int NB_MAX = 3;           // seuil de "trop de bestioles"
   static constexpr double FACTEUR = 3.;  // vive allure

public :
   void agir( Bestiole & b, const std::vector<Bestiole*> & proches, Bestiole * plusProche ) override;
   Comportement * clone() const override { return new Peureuse( *this ); }
   Couleur getCouleur() const override { return Couleur{{ 0, 0, 220 }}; }
};
#endif