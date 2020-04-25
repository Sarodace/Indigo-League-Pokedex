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

GtkWidget   *infoEmptyScreen;
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


// FUNCTION PROTOTYPES

// MAIN WINDOW FUNCTION PROTOTYPES
void handle_main_window(GtkButton *buttonClicked);
void handle_sub_window(GtkButton *buttonClicked);
gboolean switch_screens(void);
gboolean scroll_list_screen(int);
void generate_pokedex_buttons(void);
int pokemon_entry_clicked(GtkButton *buttonClicked);
gboolean keypress_function(GtkWidget *widget, GdkEventKey *event, gpointer data);

// INFO WINDOW FUNCTION PROTOTYPES
void handle_info_window(GtkButton *buttonClicked);

// FILE LOADING FUNCTION PROTOTYPES
void implement_CSS(void);
void read_from_TXT_file(GtkWidget *selectedPokemon);

// Sorting and searching 
void pokemon_search(GtkWidget *widget, gpointer user_data);

// Test evolution
int find_evolutions(int selectedPokemon);