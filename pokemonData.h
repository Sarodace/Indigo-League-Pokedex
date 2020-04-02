#ifndef POKEMONDATA_H
#define POKEMONDATA_H

#define POKEDEX_SIZE 23
#include <gtk/gtk.h>

typedef enum typeEnum {
  NONE,
  Normal,
  Fire,
  Water,
  Electric,
  Grass,
  Ice,
  Fighting,
  Poison,
  Ground,
  Flying,
  Psychic,
  Bug,
  Rock,
  Ghost,
  Dragon,
  Dark,
  Steel
} typeEnum;

const char* typeEnumStrings[] = {
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

typedef struct pokemon {
  char name[13];
  char category[15];
  int number;
  typeEnum firstType;
  typeEnum secondType;
  float height; // In meters
  int weight; // In kilograms
} pokemon;

pokemon initial[POKEDEX_SIZE] = {
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
  {"Butterfree", "Butterfly", 12, Bug, Flying, 1.1, 32.0},
  {"Weedle", "Hairy Bug", 13, Bug, Poison, 0.3, 3.2},
  {"Kakuna", "Cocoon", 14, Bug, Poison, 0.6, 10},
  {"Beedrill", "Poison Bee", 15, Bug, Poison, 1.0, 29.5},
  {"Pidgey", "Tiny Bird", 16, Normal, Flying, 0.3, 1.8},
  {"Pidgeotto", "Bird", 17, Normal, Flying, 1.1, 30},
  {"Pidgeot", "Bird", 18, Normal, Flying, 1.5, 39.5},
  {"Rattata", "Mouse", 19, Normal, NONE, 0.3, 3.5},
  {"Raticate", "Mouse", 20, Normal, NONE, 0.7, 18.5},
  {"Spearow", "Tiny Bird", 21, Normal, Flying, 0.3, 2.0},
  {"Fearow", "Beak", 22, Normal, Flying, 1.2, 38.0}
};

// TODO: Clean up this function!!!
int searchPokemonList3(GtkWidget** buttonArray,
                       const char* name, 
                       float height, 
                       int greaterHeight,
                       float weight, 
                       int greaterWeight,
                       typeEnum firstType,
                       typeEnum secondType) {
  int i; // Counter
  int j = 0; // Results
  char numberBuffer[3];
  char *ptr1, ptr2, ptr3, ptr4, ptr5;
  
  for (i=0;i<POKEDEX_SIZE-1;i++) { // I DON'T THINK I NEED THIS COUNTER
    // Set first variable to input text
    ptr1 = strcasestr(initial[i].name,name);

    // Set first variable to desired height range
    if (greaterHeight) {
      ptr2 = (initial[i].height >= height);
    } else {
      ptr2 = (initial[i].height <= height);
    }

    // Set first variable to desired weight range
    if (greaterWeight) {
      ptr3 = (initial[i].weight >= weight);
    } else {
      ptr3 = (initial[i].weight <= weight);
    }

    // First type checker
    if (firstType == NONE) {
      ptr4 = 1;
    } else {
      ptr4 = (initial[i].firstType == firstType);
    }

    // Second type checker
    if (secondType == NONE) {
      ptr5 = 1;
    } else {
      ptr5 = (initial[i].secondType == secondType);
    }

    // Check which pokemon satisfy all conditions
    if (ptr1 != NULL && ptr2 == 1 && ptr3 == 1 && ptr4 == 1 && ptr5 == 1) {
      j += 1;
      printf("GOOD: pokemon name: %s\n",initial[i].name);
      gtk_widget_show(buttonArray[i+1]);
    } else {
      printf("BAD: pokemon name: %s\n",initial[i].name);
      gtk_widget_hide(buttonArray[i+1]);
    }
  }
  printf("\n");
  return j;
}

#endif