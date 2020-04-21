#include "pokemonData.h"

// VARIABLES
// Define global variables
const char* typeEnumStrings[] = { // Potential Pokemon types (as strings)
  "",
  "Normal",
  "Fire",
  "Water",
  "Electric",
  "Grass",
  "Ice",
  "Fighting",
  "Poison",
  "Ground",
  "Flying",
  "Psychic",
  "Bug",
  "Rock",
  "Ghost",
  "Dragon",
  "Dark",
  "Steel"
};

pokemon pokedexArray[POKEDEX_SIZE] = { // Array containing all Kanto Pokemon
  {"Bulbasaur", "Seed", 1, Grass, Poison, 0.7, 6.9},
  {"Ivysaur", "Seed", 2, Grass, Poison, 1, 13},
  {"Venusaur", "Seed", 3, Grass, Poison, 2, 100},
  {"Charmander", "Lizard", 4, Fire, NONE, 0.6, 8.5},
  {"Charmeleon", "Flame", 5, Fire, NONE, 1.1, 19},
  {"Charizard", "Flame", 6, Fire, Flying, 1.7, 90.5},
  {"Squirtle", "Tiny Turtle", 7, Water, NONE, 0.5, 9},
  {"Wartortle", "Turtle", 8, Water, NONE, 1, 22.5},
  {"Blastoise", "Shellfish", 9, Water, NONE, 1.6, 85.5},
  {"Caterpie", "Worm", 10, Bug, NONE, 0.3, 2.9},
  {"Metapod", "Cocoon", 11, Bug, NONE, 0.7, 9.9},
  {"Butterfree", "Butterfly", 12, Bug, Flying, 1.1, 32},
  {"Weedle", "Hairy Bug", 13, Bug, Poison, 0.3, 3.2},
  {"Kakuna", "Cocoon", 14, Bug, Poison, 0.6, 10},
  {"Beedrill", "Poison Bee", 15, Bug, Poison, 1, 29.5},
  {"Pidgey", "Tiny Bird", 16, Normal, Flying, 0.3, 1.8},
  {"Pidgeotto", "Bird", 17, Normal, Flying, 1.1, 30},
  {"Pidgeot", "Bird", 18, Normal, Flying, 1.5, 39.5},
  {"Rattata", "Mouse", 19, Normal, NONE, 0.3, 3.5},
  {"Raticate", "Mouse", 20, Normal, NONE, 0.7, 18.5},
  {"Spearow", "Tiny Bird", 21, Normal, Flying, 0.3, 2},
  {"Fearow", "Beak", 22, Normal, Flying, 1.2, 38},
  {"Ekans", "Snake", 23, Poison, NONE, 2, 6.9},
  {"Arbok", "Cobra", 24, Poison, NONE, 3.5, 65},
  {"Pikachu", "Mouse", 25, Electric, NONE, 0.4, 6},
  {"Raichu", "Mouse", 26, Electric, NONE, 0.8, 30},
  {"Sandshrew", "Mouse", 27, Ground, NONE, 0.6, 12},
  {"Sandslash", "Mouse", 28, Ground, NONE, 1, 29.5},
  {"Nidoran♀", "Poison Pin", 29, Poison, NONE, 0.4, 7},
  {"Nidorina", "Poison Pin", 30, Poison, NONE, 0.8, 20},
  {"Nidoqueen", "Drill", 31, Poison, Ground, 1.3, 60},
  {"Nidoran♂", "Poison Pin", 32, Poison, NONE, 0.5, 9},
  {"Nidorino", "Poison Pin", 33, Poison, NONE, 0.8, 19.5},
  {"Nidoking", "Drill", 34, Poison, Ground, 1.4, 62},
  {"Clefairy", "Fairy", 35, Normal, NONE, 0.6, 7.5},
  {"Clefable", "Fairy", 36, Normal, NONE, 1.3, 40},
  {"Vulpix", "Fox", 37, Fire, NONE, 0.6, 9.9},
  {"Ninetales", "Fox", 38, Fire, NONE, 1.1, 19.9}
};

// Searches Pokemon list for Pokemon who satisfy user-provided constraints
int searchPokemonList(GtkWidget** buttonArray,
                       int desiredOrder,
                       const char* name, 
                       float height, 
                       int greaterHeight,
                       float weight, 
                       int greaterWeight,
                       typeEnum firstType,
                       typeEnum secondType) {
  int i; // Loop Counter
  int j = 0; // Relevant Pokemon counter
  char *ptr1; // Name checker variable
  int ptr2, ptr3, ptr4, ptr5; // Height, weight, and types checker variables
  
  for (i=0;i<POKEDEX_SIZE-1;i++) {
    // Check if Pokemon's name contains given string 
    ptr1 = strcasestr(pokedexArray[i].name,name);

    // Check if Pokemon's height falls within given range
    if (greaterHeight) {
      ptr2 = (pokedexArray[i].height >= height);
    } else {
      ptr2 = (pokedexArray[i].height <= height);
    }

    // Check if Pokemon's weight falls within given range
    if (greaterWeight) {
      ptr3 = (pokedexArray[i].weight >= weight);
    } else {
      ptr3 = (pokedexArray[i].weight <= weight);
    }

    // Check if Pokemon's first type matches with given first type
    if (firstType == NONE) {
      ptr4 = 1;
    } else {
      ptr4 = (pokedexArray[i].firstType == firstType);
    }

    // Check if Pokemon's second type matches with given second type
    if (secondType == NONE) {
      ptr5 = 1;
    } else {
      ptr5 = (pokedexArray[i].secondType == secondType);
    }

    // Determine whether the Pokemon satisfies all constraints
    if (ptr1 != NULL && ptr2 && ptr3 && ptr4 && ptr5) {
      j += 1;
      gtk_widget_show(buttonArray[i]);
    } else {
      gtk_widget_hide(buttonArray[i]);
    }
  }
  return j;
}