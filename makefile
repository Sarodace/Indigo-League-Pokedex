all: main.o pokemon_data.o gui.o load_files.o algorithms.o
	gcc-7 `pkg-config --cflags gtk+-3.0` main.o pokemon_data.o gui.o load_files.o algorithms.o -o main `pkg-config --libs gtk+-3.0` -rdynamic

main.o: main.c pokemon_data.h gui.h load_files.o
	gcc-7 `pkg-config --cflags gtk+-3.0` -c main.c `pkg-config --libs gtk+-3.0` -rdynamic

pokemon_data.o: pokemon_data.c pokemon_data.h
	gcc-7 `pkg-config --cflags gtk+-3.0` -c pokemon_data.c `pkg-config --libs gtk+-3.0` -rdynamic

gui.o: gui.c gui.h
	gcc-7 `pkg-config --cflags gtk+-3.0` -c gui.c `pkg-config --libs gtk+-3.0` -rdynamic

load_files.o: load_files.c load_files.h
	gcc-7 `pkg-config --cflags gtk+-3.0` -c load_files.c `pkg-config --libs gtk+-3.0` -rdynamic

algorithms.o: algorithms.c algorithms.h
	gcc-7 `pkg-config --cflags gtk+-3.0` -c algorithms.c `pkg-config --libs gtk+-3.0` -rdynamic

clean:
	rm -f main.o pokemon_data.o gui.o load_files.o main