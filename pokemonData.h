#ifndef POKEMONDATA_H
#define POKEMONDATA_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POKEDEX_SIZE 40 // REMINDER: This'll eventually go up to 151
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

extern const char* typeEnumStrings[];

typedef struct pokemon {
  char name[13];
  char category[15];
  int number;
  typeEnum firstType;
  typeEnum secondType;
  float height; // In meters
  int weight; // In kilograms
} pokemon;

extern pokemon pokedexArray[POKEDEX_SIZE];

// TODO: Clean up this function!!!
int searchPokemonList(GtkWidget** buttonArray,
                       const char* name, 
                       float height, 
                       int greaterHeight,
                       float weight, 
                       int greaterWeight,
                       typeEnum firstType,
                       typeEnum secondType);

#endif