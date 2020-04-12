#include <gtk/gtk.h>

// WINDOW VARIABLES
GtkWidget   *mainWindow;
GtkWidget   *subWindow;
GtkWidget   *infoWindow;

// MAIN WINDOW SCREENS
GtkWidget   *mainStack;
GtkWidget   *searchScreen;
GtkWidget   *listScreen;
GtkWidget   *pokemonImage;

// MAIN WINDOW LIST WIDGETS
GtkBuilder  *builder;

GtkWidget *mainWindowButton[POKEDEX_SIZE];
GtkWidget *viewBox;

// MAIN WINDOW SEARCH WIDGETS
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
GtkWidget   *entryScreen;
GtkWidget   *infoEmptyScreen;