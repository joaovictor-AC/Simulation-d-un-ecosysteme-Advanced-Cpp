#include "Milieu.h"
#include "Aleatoire.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

const T Milieu::white[] = {(T)255, (T)255, (T)255};

Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3),
                                          width(_width), height(_height),
                                          mortsAge(0), mortsCollision(0)
{

   cout << "const Milieu" << endl;

   std::srand(time(NULL));
}

Milieu::~Milieu(void)
{

   cout << "dest Milieu" << endl;
}

void Milieu::step(void)
{

   cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

   //////////////// COLLISION ////////////////////////////////

   for (size_t i = 0; i < listeBestioles.size(); i++)
   {
      for (size_t j = i + 1; j < listeBestioles.size(); j++)
      {
         Bestiole &a = listeBestioles[i]; // Bestiole 1
         Bestiole &b = listeBestioles[j]; // Bestiole 2

         if (!a.enCollision(b))
            continue;

         a.collision(b);
         b.collision(a);

         if (a.estMorte())
            ++mortsCollision;
         if (b.estMorte())
            ++mortsCollision;
      }
   }

   ////////////////////////////////////////////////////////////////

   for (std::vector<Bestiole>::iterator it = listeBestioles.begin(); it != listeBestioles.end(); ++it)
   {

      it->action(*this);
      it->draw(*this);

   } // for

   for (std::vector<Bestiole>::iterator it = listeBestioles.begin(); it != listeBestioles.end(); ++it)
   {
      if (it->estMorte())
         continue; // ya murió en este paso (colisión)

      it->vieillir();
      if (it->getAge() >= it->getAgeLimite())
      {
         it->mourir();
         ++mortsAge; // se sabe la causa
      }

   }

   // Les parcours sont termines : les effacements ne peuvent plus invalider leurs iterateurs.
   listeBestioles.erase(
      std::remove_if(listeBestioles.begin(), listeBestioles.end(),
                     [](const Bestiole& b) { return b.estMorte(); }),
      listeBestioles.end());

      
   if (Aleatoire::evenement(0.02))// Juste pour tester
   {
      addMember(Bestiole());
      listeBestioles.back().draw(*this);
   }
}

int Milieu::nbVoisins(const Bestiole &b)
{

   int nb = 0;

   for (std::vector<Bestiole>::iterator it = listeBestioles.begin(); it != listeBestioles.end(); ++it)
      if (!(b == *it) && b.jeTeVois(*it))
         ++nb;

   return nb;
}
