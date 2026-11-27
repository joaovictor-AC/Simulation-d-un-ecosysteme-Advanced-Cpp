#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "FabriqueBestioles.h"          

#include <iostream>

using namespace std;


int main()
{
   int pGregaire;
   int pPeureuse;
   int pKamikaze;
   int pPrevoyante;
   int pMultiple;
   
   cout << "Probabilite Gregaire (%) : ";
   cin >> pGregaire;
   
   if (pGregaire < 0 || pGregaire > 100) {
   
       cout << "Erreur : les probabilites doivent etre comprises entre 0 et 100."
            << endl;
       return 1;
   }
   
   cout << "Probabilite Peureuse (%) : ";
   cin >> pPeureuse;
   
   if (pPeureuse < 0 || pPeureuse > 100) {
   
       cout << "Erreur : les probabilites doivent etre comprises entre 0 et 100."
            << endl;
       return 1;
   }
   
   cout << "Probabilite Kamikaze (%) : ";
   cin >> pKamikaze;
   
   if (pKamikaze < 0 || pKamikaze > 100) {
   
       cout << "Erreur : les probabilites doivent etre comprises entre 0 et 100."
            << endl;
       return 1;
   }
   
   cout << "Probabilite Preoyante (%) : ";
   cin >> pPrevoyante;
   
   if (pPrevoyante < 0 || pPrevoyante > 100) {
   
       cout << "Erreur : les probabilites doivent etre comprises entre 0 et 100."
            << endl;
       return 1;
   }
   
   cout << "Probabilite Multiple (%) : ";
   cin >> pMultiple;
   
   if (pMultiple < 0 || pMultiple > 100) {
   
       cout << "Erreur : les probabilites doivent etre comprises entre 0 et 100."
            << endl;
       return 1;
   }
   
   int somme = pGregaire + pPeureuse + pKamikaze
             + pPrevoyante + pMultiple;
   
   if (somme != 100) {
       cout << "Erreur : la somme des probabilites doit etre egale a 100%."
            << endl;
       return 1;
   }

   DistributionComportement   distribution = {
      { TypeComportement::GREGAIRE,   static_cast<double>( pGregaire ) },
      { TypeComportement::PEUREUSE,   static_cast<double>( pPeureuse ) },
      { TypeComportement::KAMIKAZE,   static_cast<double>( pKamikaze ) },
      { TypeComportement::PREVOYANTE, static_cast<double>( pPrevoyante ) },
      { TypeComportement::MULTIPLE,   static_cast<double>( pMultiple ) }
   };
   FabriqueBestioles          fabrique( distribution );
   
   Aquarium       ecosysteme( 1500, 1200, 30 );

   for ( int i = 1; i <= 20; ++i )
      ecosysteme.getMilieu().addMember( fabrique.creerBestiole() );  
   ecosysteme.run();


   return 0;

}