main : main.cpp FabriqueBestioles.o Aquarium.o Bestiole.o Milieu.o Gregaire.o Kamikaze.o Peureuse.o Prevoyante.o PersoMultiples.o
	g++ -Wall -std=c++11 -o main main.cpp FabriqueBestioles.o Aquarium.o Bestiole.o Milieu.o Gregaire.o Kamikaze.o Peureuse.o Prevoyante.o PersoMultiples.o -I . -lX11 -lpthread

FabriqueBestioles.o : FabriqueBestioles.h FabriqueBestioles.cpp distributionComportement.h Bestiole.h Aleatoire.h Gregaire.h Peureuse.h Kamikaze.h Prevoyante.h PersoMultiples.h
	g++ -Wall -std=c++11  -c FabriqueBestioles.cpp -I .

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Bestiole.o : Bestiole.h Bestiole.cpp Comportement.h Gregaire.h Aleatoire.h Yeux.h Oreilles.h Carapace.h Nageoires.h Camouflage.h
	g++ -Wall -std=c++11  -c Bestiole.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

Gregaire.o : Gregaire.h Gregaire.cpp Comportement.h
	g++ -Wall -std=c++11  -c Gregaire.cpp -I .

Kamikaze.o : Kamikaze.h Kamikaze.cpp Comportement.h
	g++ -Wall -std=c++11  -c Kamikaze.cpp -I .

Peureuse.o : Peureuse.h Peureuse.cpp Comportement.h
	g++ -Wall -std=c++11  -c Peureuse.cpp -I .

Prevoyante.o : Prevoyante.h Prevoyante.cpp Comportement.h
	g++ -Wall -std=c++11  -c Prevoyante.cpp -I .

PersoMultiples.o : PersoMultiples.h PersoMultiples.cpp Comportement.h
	g++ -Wall -std=c++11  -c PersoMultiples.cpp -I .

clean:
	rm -rf *.o main
# Recompiler les utilisateurs des constantes quand Bestiole.h change.
Aquarium.o Milieu.o Gregaire.o Kamikaze.o Peureuse.o Prevoyante.o PersoMultiples.o: Bestiole.h
