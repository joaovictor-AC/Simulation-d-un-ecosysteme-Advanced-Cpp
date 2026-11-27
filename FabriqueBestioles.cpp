#include "FabriqueBestioles.h"
 
#include "Aleatoire.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "Prevoyante.h"
#include "PersoMultiples.h"
 
 
const double   FabriqueBestioles::PROBA_EQUIPEMENT = 0.5;
 
 
Bestiole FabriqueBestioles::creerBestiole( void ) const
{
 
   const double        PI = 3.14159265358979323846;
 
   // 1. Tirage pondéré du type de comportement (somme des pourcentages = 100)
   double              r = Aleatoire::reel( 0., 100. );
   TypeComportement    type = distribution.back().type;
 
   for ( const ConfigComportement & c : distribution ) {
      if ( r < c.probabilite ) { type = c.type; break; }
      r -= c.probabilite;
   }
 
   // 2. Caractéristiques de base : ageLimite, vitesse, taille, proba de mort en collision
   Bestiole            b( Aleatoire::entier( 1000, 2000 ), Aleatoire::reel( 1., 4. ),
                          30., Aleatoire::reel( 0.05, 0.30 ) );
 
   // 3. Equipements : chacun présent avec la probabilité PROBA_EQUIPEMENT
   if ( Aleatoire::evenement( PROBA_EQUIPEMENT ) )
      b.equiperYeux( Aleatoire::reel( 0., 30. ), Aleatoire::reel( PI / 6., 2. * PI / 3. ), Aleatoire::reel( 0.5, 1. ) );
   if ( Aleatoire::evenement( PROBA_EQUIPEMENT ) )
      b.equiperOreilles( Aleatoire::reel( 0., 50. ), Aleatoire::reel( 0.5, 1. ) );
   if ( Aleatoire::evenement( PROBA_EQUIPEMENT ) )
      b.equiperNageoires( Aleatoire::reel( 1., 2. ) );
   if ( Aleatoire::evenement( PROBA_EQUIPEMENT ) )
      b.equiperCarapace( Aleatoire::reel( 1., 3. ), Aleatoire::reel( 1., 2. ) );
   if ( Aleatoire::evenement( PROBA_EQUIPEMENT ) )
      b.equiperCamouflage( Aleatoire::reel( 0.1, 0.9 ) );
 
   // 4. Comportement tiré à l'étape 1
   switch ( type ) {
      case TypeComportement::GREGAIRE   : b.setComportement( std::unique_ptr<Comportement>( new Gregaire() ) );       break;
      case TypeComportement::PEUREUSE   : b.setComportement( std::unique_ptr<Comportement>( new Peureuse() ) );       break;
      case TypeComportement::KAMIKAZE   : b.setComportement( std::unique_ptr<Comportement>( new Kamikaze() ) );       break;
      case TypeComportement::PREVOYANTE : b.setComportement( std::unique_ptr<Comportement>( new Prevoyante() ) );     break;
      case TypeComportement::MULTIPLE   : b.setComportement( std::unique_ptr<Comportement>( new PersoMultiples() ) ); break;
   }
 
   return b;
 
}
 