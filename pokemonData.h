#ifndef POKEMONDATA_H
#define POKEMONDATA_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define POKEDEX_SIZE 40

// VARIABLES
// Declare & Define local variables
typedef enum typeEnum { // Potential Pokemon types 
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

typedef struct pokemon { // Identifying data associated with Pokemon
  char name[13];
  char category[15];
  int number;
  typeEnum firstType;
  typeEnum secondType;
  float height; // In meters
  int weight; // In kilograms
} pokemon;

// Declare global variables
extern const char* typeEnumStrings[]; // Potential Pokemon types (as strings)
extern pokemon pokedexArray[POKEDEX_SIZE]; // Array containing all Kanto Pokemon

// FUNCTION PROTOTYPES
int searchPokemonList(GtkWidget** buttonArray, 
                       int desiredOrder,
                       const char* name, 
                       float height, 
                       int greaterHeight,
                       float weight, 
                       int greaterWeight,
                       typeEnum firstType,
                       typeEnum secondType);

#endif