#include "window_functions.h"
#include "pokemonData.h"

extern const char* typeEnumStrings[];

void readFromTXTFile(GtkWidget *selectedPokemon) {
    FILE* file = fopen("pokedex_entries.txt", "r");
    char line[256];
    int i = 0;

    while (fgets(line, sizeof(line), file)) {
        i++;
        if(i == atoi(gtk_widget_get_name(selectedPokemon))) {
            gtk_label_set_text(GTK_LABEL(entryScreen),line);
        }
    }
    fclose(file);
}

//KEYPRESS HANDLER- Treat each key as a function
gboolean my_keypress_function(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_Escape) {
        if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == listScreen) {
            gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(searchScreen));
            return TRUE;
        } else {
            gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));
            gtk_stack_set_visible_child(GTK_STACK(subStack),GTK_WIDGET(subEmptyScreen));
            gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(infoEmptyScreen));
            return TRUE;
        }
    }
    if (event->keyval == GDK_KEY_Down) {
        gtk_adjustment_set_value(gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(viewBox)),gtk_adjustment_get_value(gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(viewBox))) + 100);
        printf("Works again!!!\n");
    }
    return FALSE;
}

// Handle logic in the main window
void handle_main_window(GtkButton *buttonClicked) {
    // Assemble path to pokemon image
    char selectedPokemon[30] = "assets/pokeSprites/main/";
    strcat(selectedPokemon,gtk_widget_get_name(GTK_WIDGET(buttonClicked)));
    strcat(selectedPokemon,".png");
    printf("%s\n",selectedPokemon);

    // Select relevent pokemon and then switch to child
    gtk_image_set_from_file(GTK_IMAGE(pokemonImage), selectedPokemon);
    gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(pokemonImage));
}

// Handle logic in the sub window
void handle_sub_window(GtkButton *buttonClicked) {
    // Converts button's label to a number coinceding with that pokemon
    int selectedPokemon = atoi(gtk_widget_get_name(GTK_WIDGET(buttonClicked))) - 1;
    gtk_label_set_text(GTK_LABEL(pokemonName), pokedexArray[selectedPokemon].name);

    // Assemble pokemon category from button label
    char pokemonCategoryText[25] = "The ";
    strcat(pokemonCategoryText, pokedexArray[selectedPokemon].category);
    strcat(pokemonCategoryText, " Pokemon");
    gtk_label_set_text(GTK_LABEL(pokemonCategory),pokemonCategoryText);

    // Assemble pokedex number from button label
    char pokemonDexNumber[10] = "Dex: #";
    strcat(pokemonDexNumber, gtk_widget_get_name(GTK_WIDGET(buttonClicked)));
    gtk_label_set_text(GTK_LABEL(pokemonNumber),pokemonDexNumber);

    // Format pokemon first type from button label
    gtk_label_set_text(GTK_LABEL(pokemonType1),typeEnumStrings[pokedexArray[selectedPokemon].firstType - 1]);

    // Format pokemon second type
    if (pokedexArray[selectedPokemon].secondType == 0) {
        gtk_label_set_text(GTK_LABEL(pokemonType2),"");
    } else {
        gtk_label_set_text(GTK_LABEL(pokemonType2),typeEnumStrings[pokedexArray[selectedPokemon].secondType - 1]);
    }

    //Switch sub window's focus to pokemon info
    gtk_stack_set_visible_child(GTK_STACK(subStack),GTK_WIDGET(dataScreen));
}

// Handle logic in 
void handle_info_window(GtkButton *buttonClicked) {
    gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(entryScreen));
    // readFromTXTFile(GTK_WIDGET(buttonClicked));
}

// Handle button presses
int pokemon_button_clicked (GtkButton *buttonClicked) {
    handle_main_window(buttonClicked);
    handle_sub_window(buttonClicked);
    handle_info_window(buttonClicked);
}

// Pokemon search handler
void searchPokemon(void) {
    int relevantPokemon = searchPokemonList(mainWindowButton,
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
}

// Signal handlers
int pokemon_name_search (GtkSearchEntry *entry, gpointer user_data) {
    searchPokemon();
}

int pokemon_spin_search (GtkSpinButton *entry, gpointer user_data) {
    searchPokemon();
}

void pokemon_range_search (GtkComboBox *widget, gpointer user_data) {
    searchPokemon();
}

void myCSS(void) {
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "buttonColors.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}