#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h> 

#define POKEDEX_SIZE 9

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

pokemon pokedexArray[POKEDEX_SIZE] = { // Array containing all Kanto Pokemon
  {"Bulbasaur", "Seed", 1, Grass, Poison, 0.7, 6.9, false, 0, NULL, 0},
  {"Ivysaur", "Seed", 2, Grass, Poison, 1, 13, false, 1, LEVEL_UP, 16},
  {"Venusaur", "Seed", 3, Grass, Poison, 2, 100, true, 2, LEVEL_UP, 32},
  {"Charmander", "Lizard", 4, Fire, NONE, 0.6, 8.5, false, 0, NULL, 0},
  {"Charmeleon", "Flame", 5, Fire, NONE, 1.1, 19, false, 4, LEVEL_UP, 16},
  {"Charizard", "Flame", 6, Fire, Flying, 1.7, 90.5, true, 5, LEVEL_UP, 36},
  {"Squirtle", "Tiny Turtle", 7, Water, NONE, 0.5, 9, false, 0, NULL, 0},
  {"Wartortle", "Turtle", 8, Water, NONE, 1, 22.5, false, 7, LEVEL_UP, 16},
  {"Blastoise", "Shellfish", 9, Water, NONE, 1.6, 85.5, true, 8, LEVEL_UP, 36}
};












void print_pokemon_struct_array(struct pokemon *array, size_t len) { 
    size_t i;
 
    for(i=0; i<len; i++) 
        printf("[ Name: %s \t Number: %d Height: %f Weight: %f ]\n", 
          array[i].name, array[i].number, array[i].height, array[i].weight);
 
    puts("--");
} 

int sort_numerical(const void *a, const void *b) { 
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;
    return ia->number - ib->number;
}

int sort_weight_ascending(const void *a, const void *b) { 
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;
    return (int)(100.f*ia->weight - 100.f*ib->weight);
}

int sort_weight_descending(const void *a, const void *b) { 
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;
    return (int)(100.f*ib->weight - 100.f*ia->weight);
}

int sort_height_ascending(const void *a, const void *b) {
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;
    return (int)(100.f*ia->height - 100.f*ib->height);
}

int sort_height_descending(const void *a, const void *b) { 
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;
    return (int)(100.f*ib->height - 100.f*ia->height);
}

int struct_pokemon_by_name(const void *a, const void *b) {
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;
    return strcmp(ia->name, ib->name);
}
 
void sorting_functions(void) { 
    size_t pokemon_len = sizeof(pokedexArray) / sizeof(struct pokemon);

    printf("*** Print struct sorted by NUMERICAL\n");
    qsort(pokedexArray, pokemon_len, sizeof(pokemon), sort_numerical);
    print_pokemon_struct_array(pokedexArray,pokemon_len);

    printf("*** Print struct sorted by ALPHABETICAL\n");
    qsort(pokedexArray, pokemon_len, sizeof(pokemon), struct_pokemon_by_name);
    print_pokemon_struct_array(pokedexArray,pokemon_len);

    printf("*** Print struct sorted by WEIGHT (light->heavy)\n");
    qsort(pokedexArray, pokemon_len, sizeof(pokemon), sort_weight_ascending);
    print_pokemon_struct_array(pokedexArray,pokemon_len);

    printf("*** Print struct sorted by WEIGHT (heavy->light)\n");
    qsort(pokedexArray, pokemon_len, sizeof(pokemon), sort_weight_descending);
    print_pokemon_struct_array(pokedexArray,pokemon_len);

    printf("*** Print struct sorted by HEIGHT (short->tall)\n");
    qsort(pokedexArray, pokemon_len, sizeof(pokemon), sort_height_ascending);
    print_pokemon_struct_array(pokedexArray,pokemon_len);

    printf("*** Print struct sorted by HEIGHT (tall->short)\n");
    qsort(pokedexArray, pokemon_len, sizeof(pokemon), sort_height_descending);
    print_pokemon_struct_array(pokedexArray,pokemon_len);
}

/* MAIN program (calls all other examples) */ 
int main() {
    sorting_functions();
    return 0;
}