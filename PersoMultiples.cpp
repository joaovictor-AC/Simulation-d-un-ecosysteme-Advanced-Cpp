// PersoMultiples.cpp
#include "PersoMultiples.h"
#include "Bestiole.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "Prevoyante.h"
#include <cstdlib>
#include "Aleatoire.h"

PersoMultiples::PersoMultiples()
   : courant( nullptr ), compteur( 0 ), vitesseNormale( 0. ), init( false )
{
}

PersoMultiples::PersoMultiples( const PersoMultiples & p )
   : courant( p.courant ? p.courant->clone() : nullptr ),
     compteur( p.compteur ), vitesseNormale( p.vitesseNormale ), init( p.init )
{
}

PersoMultiples::~PersoMultiples()
{
   delete courant;
}

void PersoMultiples::changer( Bestiole & b )
{
   delete courant;
   b.setVitesse( vitesseNormale );          // annule une éventuelle fuite en cours

   switch ( rand() % 4 ) {                  // jamais PersoMultiples : pas de récursion
      case 0 : courant = new Gregaire();   break;
      case 1 : courant = new Peureuse();   break;
      case 2 : courant = new Kamikaze();   break;
      default: courant = new Prevoyante(); break;
   }
   compteur = Aleatoire::entier(Bestiole::DUREE_PERSONNALITE_MIN,
                               Bestiole::DUREE_PERSONNALITE_MAX);
}

void PersoMultiples::agir( Bestiole & b, const std::vector<Bestiole*> & proches, Bestiole * plusProche )
{
   if ( !init ) { vitesseNormale = b.getVitesse(); init = true; }

   if ( courant == nullptr || --compteur <= 0 )
      changer( b );

   courant->agir( b, proches, plusProche );
}