#include "pokemon_data.h"

// VARIABLES
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
  {"Bulbasaur", "Seed", 1, Grass, Poison, 0.7, 6.9, FALSE, 0, NULL, 0},
  {"Ivysaur", "Seed", 2, Grass, Poison, 1, 13, FALSE, 1, LEVEL_UP, 16},
  {"Venusaur", "Seed", 3, Grass, Poison, 2, 100, TRUE, 2, LEVEL_UP, 32},
  {"Charmander", "Lizard", 4, Fire, NONE, 0.6, 8.5, FALSE, 0, NULL, 0},
  {"Charmeleon", "Flame", 5, Fire, NONE, 1.1, 19, FALSE, 4, LEVEL_UP, 16},
  {"Charizard", "Flame", 6, Fire, Flying, 1.7, 90.5, TRUE, 5, LEVEL_UP, 36},
  {"Squirtle", "Tiny Turtle", 7, Water, NONE, 0.5, 9, FALSE, 0, NULL, 0},
  {"Wartortle", "Turtle", 8, Water, NONE, 1, 22.5, FALSE, 7, LEVEL_UP, 16},
  {"Blastoise", "Shellfish", 9, Water, NONE, 1.6, 85.5, TRUE, 8, LEVEL_UP, 36},
  {"Caterpie", "Worm", 10, Bug, NONE, 0.3, 2.99, FALSE, 0, LEVEL_UP, 0},
  {"Metapod", "Cocoon", 11, Bug, NONE, 0.7, 9.9, FALSE, 10, LEVEL_UP, 7},
  {"Butterfree", "Butterfly", 12, Bug, Flying, 1.1, 32, TRUE, 11, LEVEL_UP, 10},
  {"Weedle", "Hairy Bug", 13, Bug, Poison, 0.3, 3.2, FALSE, 0, LEVEL_UP, 0},
  {"Kakuna", "Cocoon", 14, Bug, Poison, 0.6, 10, FALSE, 13, LEVEL_UP, 7},
  {"Beedrill", "Poison Bee", 15, Bug, Poison, 1, 29.5, TRUE, 14, LEVEL_UP, 10},
  {"Pidgey", "Tiny Bird", 16, Normal, Flying, 0.3, 1.8, FALSE, 0, LEVEL_UP, 0},
  {"Pidgeotto", "Bird", 17, Normal, Flying, 1.1, 30, FALSE, 16, LEVEL_UP, 18},
  {"Pidgeot", "Bird", 18, Normal, Flying, 1.5, 39.5, TRUE, 17, LEVEL_UP, 36},
  {"Rattata", "Mouse", 19, Normal, NONE, 0.3, 3.5, FALSE, 0, LEVEL_UP, 0}, //nc
  {"Raticate", "Mouse", 20, Normal, NONE, 0.7, 18.5, TRUE, 19, LEVEL_UP, 20},
  {"Spearow", "Tiny Bird", 21, Normal, Flying, 0.3, 2, FALSE, 0, LEVEL_UP, 0},
  {"Fearow", "Beak", 22, Normal, Flying, 1.2, 38, TRUE, 21, LEVEL_UP, 20},//nc
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
  {"Ninetales", "Fox", 38, Fire, NONE, 1.1, 19.9},
  {"Jigglypuff", "Fox", 39, Normal, NONE, 0.6, 9.9},
  {"Wigglypuff", "Fox", 40, Normal, NONE, 1.1, 19.9},
  
  // {"Eevee", "Fox", 37, Fire, NONE, 0.6, 9.9, FALSE, NULL, NULL},
  // {"Jolteon", "Fox", 38, Fire, NONE, 1.1, 19.9, TRUE, 140, THUNDER_STONE},
  // {"Flareon", "Fox", 38, Fire, NONE, 1.1, 19.9, TRUE, 140, FIRE_STONE},
  // {"Vaporeon", "Fox", 38, Fire, NONE, 1.1, 19.9, TRUE, 140, WATER_STONE},
};