#ifndef POKEMONDATA_H
#define POKEMONDATA_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <stdbool.h> 

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

// typedef enum canEvolveEnum {
//   CANNOT_EVOLVE,
//   CAN_EVOLVE,
//   MULTIPLE_EVOLUTIONS
// } canEvolveEnum;

typedef enum evolutionEnum {
  LEVEL_UP,
  TRADE,
  FIRE_STONE,
  WATER_STONE,
  THUNDER_STONE,
  LEAF_STONE,
} evolutionEnum;

typedef struct pokemon { // Identifying data associated with Pokemon
  char name[13];
  char category[15];
  int number;
  typeEnum firstType;
  typeEnum secondType;
  float height; // In meters
  float weight; // In kilograms
  bool finalForm; // -1 Can't evolve, 0 No, 1 yes
  int evolvesFrom;
  evolutionEnum *evolutionMethod;
  int level;
} pokemon;

// Declare global variables
extern const char* typeEnumStrings[]; // Potential Pokemon types (as strings)
extern pokemon pokedexArray[POKEDEX_SIZE]; // Array containing all Kanto Pokemon

// FUNCTION PROTOTYPES
int search_Pokemon_list(GtkWidget** buttonArray, 
                       int desiredOrder,
                       const char* name, 
                       float height, 
                       int greaterHeight,
                       float weight, 
                       int greaterWeight,
                       typeEnum firstType,
                       typeEnum secondType);

#endif