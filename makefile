main: main.o pokemonData.o window_functions.o
	gcc-7 `pkg-config --cflags gtk+-3.0` main.o pokemonData.o window_functions.o -o main `pkg-config --libs gtk+-3.0` -rdynamic

main.o: main.c pokemonData.h window_functions.h
	gcc-7 `pkg-config --cflags gtk+-3.0` -c main.c `pkg-config --libs gtk+-3.0` -rdynamic

pokemonData.o: pokemonData.c pokemonData.h
	gcc-7 `pkg-config --cflags gtk+-3.0` -c pokemonData.c `pkg-config --libs gtk+-3.0` -rdynamic

window_functions.o: window_functions.c window_functions.h pokemonData.h
	gcc-7 `pkg-config --cflags gtk+-3.0` -c window_functions.c `pkg-config --libs gtk+-3.0` -rdynamic

clean:
	rm -f main.o pokemonData.o window_functions.o main