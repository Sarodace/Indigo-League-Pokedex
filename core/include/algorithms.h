#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define _GNU_SOURCE
#include <gtk/gtk.h>
#include "gui.h"
#include "css_styling.h"
#include "pokemon_data.h"
#include <stdlib.h>
#include <string.h>

int threeStagePokemon;
int pokemonStage;
pokemon pokedexEntries[POKEDEX_SIZE];

// Sorting and searching
int fill_pokedex_array(void);

void generate_pokedex_buttons(void);
void pokemon_search(GtkWidget *widget, gpointer user_data);
int find_evolutions(int selectedPokemon);
int fill_pokemon_evolution_entries(char*, int, int);
int sort_pokedex_entries(int sortingStyle);
int compare_weight(const void *pa, const void *pb);
void rearrange_buttons(void);
int search_pokemon_list(GtkWidget** buttonArray,
                       int desiredOrder,
                       const char* name,
                       float height,
                       int greaterHeight,
                       float weight,
                       int greaterWeight,
                       typeEnum firstType,
                       typeEnum secondType);
// void set_pokemon_description_title(GtkWidget *widget);
void populate_description_screen(int selectedPokemon);


// Sorting alogorithms
int sort_alphabetical(const void *a, const void *b);
int sort_numerical(const void *a, const void *b);
int sort_weight_ascending(const void *a, const void *b);
int sort_weight_descending(const void *a, const void *b);
int sort_height_ascending(const void *a, const void *b);
int sort_height_descending(const void *a, const void *b);

#endif