#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include "pokemon_data.h"
#include "load_files.h"
#include "algorithms.h"


// VARIABLES
// WINDOW VARIABLES
GtkWidget   *mainWindow;
GtkWidget   *subWindow;
GtkWidget   *infoWindow;

// MAIN WINDOW SCREENS & BUILDER VARIABLE
GtkWidget   *mainStack;
GtkWidget   *searchScreen;
GtkWidget   *listScreen;
GtkWidget   *pokemonImage;
GtkBuilder  *builder;

// MAIN WINDOW LIST WIDGETS
GtkWidget *viewBox;
GtkWidget *pokemonEntryList;
GtkWidget *mainWindowButton[POKEDEX_SIZE];


// MAIN WINDOW SEARCH WIDGETS
GtkWidget   *orderComboBox;

GtkWidget   *pokemonNameSearchEntry;
GtkWidget   *pokemonHeightSpinButton;
GtkWidget   *pokemonWeightSpinButton;
GtkWidget   *pokemonResults;

GtkWidget   *heightComboBox;
GtkWidget   *weightComboBox;

GtkWidget   *pokemonFirstTypeSearch;
GtkWidget   *pokemonSecondTypeSearch;

// SUB WINDOW SCREENS
GtkWidget   *subStack;
GtkWidget   *dataScreen;
GtkWidget   *subEmptyScreen;

// SUB WINDOW WIDGETS
GtkWidget   *pokemonName;
GtkWidget   *pokemonCategory;
GtkWidget   *pokemonNumber;
GtkWidget   *pokemonType1;
GtkWidget   *pokemonType2;

// INFO WINDOW SCREENS
GtkWidget   *infoStack;

GtkWidget   *infoEmptyScreen;
GtkWidget   *descriptionScreen;
GtkWidget   *entryScreen;
GtkWidget   *threeTierEvolution;
GtkWidget   *twoTierEvolution;

// MAIN WINDOW MENU BAR
GtkWidget   *searchScreenIndicator;
GtkWidget   *listScreenIndicator;
GtkWidget   *displayScreenIndicator;

// TODO: RENAME
GtkWidget   *descriptionScreenIndicator;
GtkWidget   *evolutionScreenIndicator;

// Evolution screen variables
// 3-Tier
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

// evolution methods
GtkWidget   *twoTier_evolutionSwitcher;
GtkWidget   *threeTier_evolutionSwitcher;
GtkWidget   *twoTier_evolutionMethod;
GtkWidget   *threeTier_evolutionMethod;

GtkWidget   *testScreen;
GtkWidget   *testScreenTwo;

GtkWidget   *menuBarStack;
GtkWidget   *mainScreenBar;
GtkWidget   *displayScreenBar;

// Infostack
GtkWidget   *infoStackName;
GtkWidget   *infoStackSpecies;
GtkWidget   *infoStackBar;

// Declare variables for bottom menu bar
GtkWidget   *submenuBarRevealer;
GtkWidget   *submenuBarStack;
GtkWidget   *submenuBarStack_Search;
GtkWidget   *submenuBarStack_List;
GtkWidget   *submenuBarStack_Define;
GtkWidget   *submenuBarStack_Evos;

GtkAdjustment *viewWindow;
int currentHeight;
int currentlySelectedPokemon;

// FUNCTION PROTOTYPES
void handle_main_window(GtkButton *buttonClicked);
void handle_info_window(GtkButton *buttonClicked);
void handle_sub_window(GtkButton *buttonClicked);
gboolean switch_screens(void);
gboolean scroll_list_screen(int);
void pokemon_entry_clicked(GtkButton *buttonClicked);
gboolean keypress_function(GtkWidget *widget, GdkEventKey *event, gpointer data);

int animate_pokemon_evolution_cards(int pokemonStage, int buttonPress);

#endif