all: shikaku

shikaku: shikaku.o tablero.o interfaz.o
	g++ -std=c++23 -g -O1 shikaku.o tablero.o interfaz.o -o shikaku

shikaku.o: shikaku.cxx tablero.h interfaz.h
	g++ -std=c++23 -g -O1 -c shikaku.cxx

tablero.o: tablero.cxx tablero.h
	g++ -std=c++23 -g -O1 -c tablero.cxx

interfaz.o: interfaz.cxx interfaz.h tablero.h
	g++ -std=c++23 -g -O1 -c interfaz.cxx

clean:
	rm -rf *.o shikaku