all: main.o pokemon_data.o gui.o load_files.o algorithms.o css_styling.o
	gcc-7 -iquote core/include `pkg-config --cflags gtk+-3.0` main.o pokemon_data.o gui.o load_files.o algorithms.o css_styling.o -o main `pkg-config --libs gtk+-3.0` -rdynamic

main.o: core/source/main.c core/include/pokemon_data.h core/include/gui.h core/include/load_files.h
	gcc-7 -iquote core/include `pkg-config --cflags gtk+-3.0` -c core/source/main.c `pkg-config --libs gtk+-3.0` -rdynamic

pokemon_data.o: core/source/pokemon_data.c core/include/pokemon_data.h
	gcc-7 -iquote core/include `pkg-config --cflags gtk+-3.0` -c core/source/pokemon_data.c `pkg-config --libs gtk+-3.0` -rdynamic

gui.o: core/source/gui.c core/include/gui.h
	gcc-7 -iquote core/include `pkg-config --cflags gtk+-3.0` -c core/source/gui.c `pkg-config --libs gtk+-3.0` -rdynamic

load_files.o: core/source/load_files.c core/include/load_files.h
	gcc-7 -iquote core/include `pkg-config --cflags gtk+-3.0` -c core/source/load_files.c `pkg-config --libs gtk+-3.0` -rdynamic

algorithms.o: core/source/algorithms.c core/include/algorithms.h
	gcc-7 -iquote core/include `pkg-config --cflags gtk+-3.0` -c core/source/algorithms.c `pkg-config --libs gtk+-3.0` -rdynamic

css_styling.o: core/source/css_styling.c core/include/css_styling.h
	gcc-7 -iquote core/include `pkg-config --cflags gtk+-3.0` -c core/source/css_styling.c `pkg-config --libs gtk+-3.0` -rdynamic

clean:
	rm -f main.o pokemon_data.o gui.o load_files.o algorithms.o css_styling.o main