#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "pokemonData.h"

// Make them global
char str[5];

// WINDOW VARIABLES
GtkWidget   *mainWindow;
GtkWidget   *subWindow;

// MAIN WINDOW SCREENS
GtkWidget   *mainStack;
GtkWidget   *searchScreen;
GtkWidget   *listScreen;
GtkWidget   *pokemonImage;

// MAIN WINDOW LIST WIDGETS
GtkBuilder  *builder;

GtkWidget *mainWindowButton[POKEDEX_SIZE];

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
GtkWidget   *emptyScreen;

// SUB WINDOW WIDGETS
GtkWidget   *pokemonName;
GtkWidget   *pokemonCategory;
GtkWidget   *pokemonNumber;
GtkWidget   *pokemonType1;
GtkWidget   *pokemonType2;

// Handle "ESC"
gboolean my_keypress_function(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_Escape) {
        if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == listScreen) {
            gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(searchScreen));
            return TRUE;
        } else {
            gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));
            gtk_stack_set_visible_child(GTK_STACK(subStack),GTK_WIDGET(emptyScreen));
            // for (int i = 1; i <= 22; i++) {
            //     gtk_widget_show(GTK_WIDGET(mainWindowButton[i]));
            // }
            return TRUE;
        }
    }
    return FALSE;
}

void handle_main_window(GtkButton *buttonClicked) {
    // Assemble string
    char selectedPokemon[30] = "assets/pokeSprites/main/";
    strcat(selectedPokemon,gtk_widget_get_name(GTK_WIDGET(buttonClicked)));
    strcat(selectedPokemon,".png");
    printf("%s\n",selectedPokemon);

    // Select relevent pokemon and then switch to child
    gtk_image_set_from_file(GTK_IMAGE(pokemonImage), selectedPokemon);
    gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(pokemonImage));
}

void handle_sub_window(GtkButton *buttonClicked) {
    // Converts button's label to a number coinceding with that pokemon
    int selectedPokemon = atoi(gtk_widget_get_name(GTK_WIDGET(buttonClicked))) - 1;
    gtk_label_set_text(GTK_LABEL(pokemonName), initial[selectedPokemon].name);

    // Format pokemon category
    char pokemonCategoryText[25] = "The ";
    strcat(pokemonCategoryText, initial[selectedPokemon].category);
    strcat(pokemonCategoryText, " Pokemon");
    gtk_label_set_text(GTK_LABEL(pokemonCategory),pokemonCategoryText);

    // Format pokemon dex number
    char pokemonDexNumber[10] = "Dex: #";
    strcat(pokemonDexNumber, gtk_widget_get_name(GTK_WIDGET(buttonClicked)));
    gtk_label_set_text(GTK_LABEL(pokemonNumber),pokemonDexNumber);

    // Format pokemon first type
    gtk_label_set_text(GTK_LABEL(pokemonType1),typeEnumStrings[initial[selectedPokemon].firstType - 1]);

    // Format pokemon second type
    if (initial[selectedPokemon].secondType == 0) {
        gtk_label_set_text(GTK_LABEL(pokemonType2),"");
    } else {
        gtk_label_set_text(GTK_LABEL(pokemonType2),typeEnumStrings[initial[selectedPokemon].secondType - 1]);
    }

    //Switch child
    gtk_stack_set_visible_child(GTK_STACK(subStack),GTK_WIDGET(dataScreen));
}

// Handle button presses
int pokemon_button_clicked (GtkButton *buttonClicked) {
    handle_main_window(buttonClicked);
    handle_sub_window(buttonClicked);
}

// Pokemon search handler
void searchPokemon() {
    int relevantPokemon = searchPokemonList3(mainWindowButton,
                                            gtk_entry_get_text(GTK_ENTRY(pokemonNameSearchEntry)),
                                            gtk_spin_button_get_value(GTK_SPIN_BUTTON(pokemonHeightSpinButton)),
                                            gtk_combo_box_get_active(GTK_COMBO_BOX(heightComboBox)),
                                            gtk_spin_button_get_value(GTK_SPIN_BUTTON(pokemonWeightSpinButton)),
                                            gtk_combo_box_get_active(GTK_COMBO_BOX(weightComboBox)),
                                            gtk_combo_box_get_active(GTK_COMBO_BOX(pokemonFirstTypeSearch)),
                                            gtk_combo_box_get_active(GTK_COMBO_BOX(pokemonSecondTypeSearch)));
    char relevantPokemonString[25];
    sprintf(relevantPokemonString,"%d",relevantPokemon);
    strcat(relevantPokemonString, " results(s) found");

    gtk_label_set_text(GTK_LABEL(pokemonResults), relevantPokemonString);
    // gtk_widget_hide(GTK_WIDGET(button1));
}

int pokemon_name_search (GtkSearchEntry *entry, gpointer user_data) {
    searchPokemon();
}

int pokemon_spin_search (GtkSpinButton *entry, gpointer user_data) {
    searchPokemon();
}

//RENAME
void pokemon_range_search (GtkComboBox *widget, gpointer user_data) {
    searchPokemon();
}

int main(int argc, char *argv[]) {
    // init GTK
    gtk_init(&argc, &argv);

    // Build windows and connect signals described in Glade file
    builder = gtk_builder_new_from_file ("pokedex2.glade");
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    subWindow = GTK_WIDGET(gtk_builder_get_object(builder, "subWindow"));
    gtk_widget_add_events(mainWindow, GDK_KEY_PRESS_MASK);

    g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT (mainWindow), "key_press_event", G_CALLBACK (my_keypress_function), NULL);
    gtk_builder_connect_signals(builder, NULL);

    // Build widgets decribed in Glade file
    // MAIN WINDOW --- LIST
    for (int i = 1; i <= 22; i++) {
        sprintf(str,"%d",i);
        mainWindowButton[i] = GTK_WIDGET(gtk_builder_get_object(builder, str));
    }

    mainStack = GTK_WIDGET(gtk_builder_get_object(builder, "mainStack"));
    searchScreen = GTK_WIDGET(gtk_builder_get_object(builder, "searchScreen"));
    listScreen = GTK_WIDGET(gtk_builder_get_object(builder, "listScreen"));
    pokemonImage = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonImage"));

    // MAIN WINDOW --- SEARCH
    pokemonResults = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonResults"));
    pokemonNameSearchEntry = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonNameSearchEntry"));
    pokemonHeightSpinButton = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonHeightSpinButton"));
    pokemonWeightSpinButton = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonWeightSpinButton"));

    heightComboBox = GTK_WIDGET(gtk_builder_get_object(builder, "heightComboBox"));
    weightComboBox = GTK_WIDGET(gtk_builder_get_object(builder, "weightComboBox"));

    pokemonFirstTypeSearch = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonFirstTypeSearch"));
    pokemonSecondTypeSearch = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonSecondTypeSearch"));

    // SUB WINDOW
    pokemonName = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonName"));
    pokemonCategory = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonCategory"));
    pokemonNumber = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonNumber"));
    pokemonType1 = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonType1"));
    pokemonType2 = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonType2"));

    subStack = GTK_WIDGET(gtk_builder_get_object(builder, "subStack"));
    dataScreen = GTK_WIDGET(gtk_builder_get_object(builder, "dataScreen"));
    emptyScreen = GTK_WIDGET(gtk_builder_get_object(builder, "emptyScreen"));

    // Display the GUI
    gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));
    gtk_widget_show(mainWindow);
    gtk_widget_show(subWindow);
    gtk_main();

    return EXIT_SUCCESS;
}