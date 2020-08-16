#ifndef POKEMON_DATA_H
#define POKEMON_DATA_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <stdbool.h> 

#define POKEDEX_SIZE 94
#define POKEMON_TYPES 18

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

typedef enum evolutionEnum {
  NO_EVO,
  LEVEL_UP,
  TRADE,
  FIRE_STONE,
  WATER_STONE,
  THUNDER_STONE,
  LEAF_STONE,
  MOON_STONE
} evolutionEnum;

typedef struct pokemon { // Identifying data associated with Pokemon
  char name[20];
  char category[20];
  int number;
  typeEnum firstType;
  typeEnum secondType;
  float height; // In meters
  float weight; // In kilograms
  bool finalForm; // 0 No, 1 yes
  int evolvesFrom;
  evolutionEnum evolutionMethod;
  int level;
} pokemon;

// Declare global variables
extern const char* typeEnumStrings[]; // Potential Pokemon types (as strings)
extern const char* typeEnumStrings_CSS[]; // Potential Pokemon types (as strings)
extern pokemon pokedexArray[POKEDEX_SIZE]; // Array containing all Kanto Pokemon

#endif