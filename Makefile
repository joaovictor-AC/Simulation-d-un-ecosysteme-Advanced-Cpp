main : main.cpp Aquarium.o Bestiole.o Milieu.o Gregaire.o Kamikaze.o Peureuse.o Prevoyante.o PersoMultiples.o Yeux.o Oreilles.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Bestiole.o Milieu.o Gregaire.o Kamikaze.o Peureuse.o Prevoyante.o PersoMultiples.o Yeux.o Oreilles.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Bestiole.o : Bestiole.h Bestiole.cpp
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

Yeux.o : Yeux.h Yeux.cpp
	g++ -Wall -std=c++11  -c Yeux.cpp -I .

Oreilles.o : Oreilles.h Oreilles.cpp
	g++ -Wall -std=c++11  -c Oreilles.cpp -I .

clean:
	rm -rf *.o main