all: shikaku

shikaku: shikaku.o tablero.o human.o fuerza_bruta.o heuristica.o
	g++ -std=c++23 -g -O1 -Wall shikaku.o tablero.o human.o fuerza_bruta.o heuristica.o -o shikaku

shikaku.o: shikaku.cxx human.h fuerza_bruta.h heuristica.h tablero.h
	g++ -std=c++23 -g -O1 -Wall -c shikaku.cxx

tablero.o: tablero.cxx tablero.h
	g++ -std=c++23 -g -O1 -Wall -c tablero.cxx

human.o: human.cxx human.h tablero.h
	g++ -std=c++23 -g -O1 -Wall -c human.cxx

fuerza_bruta.o: fuerza_bruta.cxx fuerza_bruta.h tablero.h
	g++ -std=c++23 -g -O1 -Wall -c fuerza_bruta.cxx

heuristica.o: heuristica.cxx heuristica.h tablero.h
	g++ -std=c++23 -g -O1 -Wall -c heuristica.cxx

clean:
	rm -rf *.o shikaku