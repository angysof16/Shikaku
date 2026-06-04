SRCS = src/shikaku.cxx \
    src/tablero.cxx \
    src/human.cxx \
    src/fuerza_bruta.cxx \
    src/heuristica.cxx

OBJS = $(SRCS:src/%.cxx=build/%.o)

all: shikaku

shikaku: $(OBJS)
	g++ -std=c++23 -g -O1 -Wall -Iinclude $(OBJS) -o shikaku

build/%.o: src/%.cxx | build
	g++ -std=c++23 -g -O1 -Wall -Iinclude -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build shikaku
