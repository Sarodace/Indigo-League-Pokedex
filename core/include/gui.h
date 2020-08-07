#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include "pokemon_data.h"
#include "load_files.h"
#include "algorithms.h"

// VARIABLES
GtkWidget   *mainWindow;
GtkWidget   *mainStack;
GtkBuilder  *builder;

// Search screen variables
GtkWidget   *searchScreen;

GtkWidget   *orderComboBox;
GtkWidget   *pokemonNameSearchEntry;
GtkWidget   *pokemonFirstTypeSearch;
GtkWidget   *pokemonSecondTypeSearch;
GtkWidget   *weightComboBox;
GtkWidget   *pokemonWeightSpinButton;
GtkWidget   *heightComboBox;
GtkWidget   *pokemonHeightSpinButton;
GtkWidget   *pokemonResults;

// List screen variables
GtkWidget   *listScreen;
GtkWidget   *viewBox;
GtkWidget   *pokemonEntryList;
GtkWidget   *mainWindowButton[POKEDEX_SIZE]; // TODO: RENAME

// Decription screen variables
GtkWidget   *descriptionScreen;

// Three-tier screen variables
GtkWidget   *threeTierScreen;

GtkWidget   *threeTier_1stImage;
GtkWidget   *threeTier_1stNumber;
GtkWidget   *threeTier_1stName;
GtkWidget   *threeTier_1stType1;
GtkWidget   *threeTier_1stType2;

GtkWidget   *threeTier_2ndImage;
GtkWidget   *threeTier_2ndNumber;
GtkWidget   *threeTier_2ndName;
GtkWidget   *threeTier_2ndType1;
GtkWidget   *threeTier_2ndType2;

GtkWidget   *threeTier_3rdImage;
GtkWidget   *threeTier_3rdNumber;
GtkWidget   *threeTier_3rdName;
GtkWidget   *threeTier_3rdType1;
GtkWidget   *threeTier_3rdType2;

GtkWidget   *threeTier_1stEvolution;
GtkWidget   *threeTier_2ndEvolution;
GtkWidget   *threeTier_evolutionSwitcher;
GtkWidget   *threeTier_evolutionMethod;

// 2-stage evolutionary family
GtkWidget   *twoTierScreen;

GtkWidget   *twoTier_1stImage;
GtkWidget   *twoTier_1stNumber;
GtkWidget   *twoTier_1stName;
GtkWidget   *twoTier_1stType1;
GtkWidget   *twoTier_1stType2;

GtkWidget   *twoTier_2ndImage;
GtkWidget   *twoTier_2ndNumber;
GtkWidget   *twoTier_2ndName;
GtkWidget   *twoTier_2ndType1;
GtkWidget   *twoTier_2ndType2;

GtkWidget   *twoTier_1stEvolution;
GtkWidget   *twoTier_evolutionSwitcher;
GtkWidget   *twoTier_evolutionMethod;

// Menu bar
GtkWidget   *searchScreenRevealer;
GtkWidget   *listScreenRevealer;
GtkWidget   *descriptionScreenRevealer;
GtkWidget   *evolutionScreenRevealer;

// Submenu bar
GtkWidget   *submenuBarStack;
GtkWidget   *submenuBarStack_Search;
GtkWidget   *submenuBarStack_List;
GtkWidget   *submenuBarStack_Description;
GtkWidget   *submenuBarStack_Evolution;

GtkAdjustment *viewWindow;

int currentHeight;
int currentlySelectedPokemon;
bool selectingPokemon;

// FUNCTION PROTOTYPES
void handle_main_window(GtkButton *buttonClicked);
gboolean switch_screens(void);
gboolean scroll_list_screen(int);
void pokemon_entry_clicked(GtkButton *buttonClicked);
gboolean keypress_function(GtkWidget *widget, GdkEventKey *event, gpointer data);

int animate_pokemon_evolution_cards(int pokemonStage, int buttonPress);

#endif