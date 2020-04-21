#include <gtk/gtk.h>

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
GtkWidget *mainWindowButton[40];
GtkWidget *viewBox;

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
GtkWidget   *entryScreen;
GtkWidget   *infoEmptyScreen;

// MAIN WINDOW MENU BAR
GtkWidget   *searchScreenIndicator;
GtkWidget   *listScreenIndicator;
GtkWidget   *displayScreenIndicator;

//FUNCTION PROTOTYPES
void readFromTXTFile(GtkWidget *selectedPokemon);
gboolean keypress_function(GtkWidget *widget, GdkEventKey *event, gpointer data);
void handle_main_window(GtkButton *buttonClicked);
void handle_sub_window(GtkButton *buttonClicked);
void handle_info_window(GtkButton *buttonClicked);
int pokemon_button_clicked (GtkButton *buttonClicked);
void search_pokemon(void);
int pokemon_name_search (GtkSearchEntry *entry, gpointer user_data);
int pokemon_spin_search (GtkSpinButton *entry, gpointer user_data);
void pokemon_range_search (GtkComboBox *widget, gpointer user_data);
void implement_CSS(void);
gboolean switch_screens(void);
gboolean scroll_list_screen(int);
void generatePokedexButtons(void);

int sortPokemonList(int);