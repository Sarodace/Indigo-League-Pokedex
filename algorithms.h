#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <gtk/gtk.h>
#include "gui.h"

int godVar;

// Sorting and searching
void generate_pokedex_buttons(void);
void pokemon_search(GtkWidget *widget, gpointer user_data);
int find_evolutions(int selectedPokemon);
int fill_pokemon_evolution_entries(char*,int,int);

#endif