#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define _GNU_SOURCE
#include <gtk/gtk.h>
#include "gui.h"
#include "css_styling.h"
#include <stdlib.h>
#include <string.h>

int godVar;

// Sorting and searching
// void style_given_element(const char* elementID, const char* cssTag);
// void style_evolution_card(const char* elementID, const char* cssTag);
void generate_pokedex_buttons(void);
void pokemon_search(GtkWidget *widget, gpointer user_data);
int find_evolutions(int selectedPokemon);
int fill_pokemon_evolution_entries(char*,int,int);
int sort_pokedex_entries(int sortingStyle);
int compare_weight(const void *pa,const void *pb);
void rearrange_buttons(void);
void test_sorting_functions(void);
int search_Pokemon_List(GtkWidget** buttonArray, 
                       int desiredOrder,
                       const char* name, 
                       float height, 
                       int greaterHeight,
                       float weight, 
                       int greaterWeight,
                       typeEnum firstType,
                       typeEnum secondType);

// Sorting alogorithms
int sort_alphabetical(const void *a, const void *b);
int sort_numerical(const void *a, const void *b);
int sort_weight_ascending(const void *a, const void *b);
int sort_weight_descending(const void *a, const void *b);
int sort_height_ascending(const void *a, const void *b);
int sort_height_descending(const void *a, const void *b);

#endif