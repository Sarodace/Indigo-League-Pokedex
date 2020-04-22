#include <time.h>

#include "window_functions.h"
#include "pokemonData.h"

// VARIABLES
// Declare global variables
extern const char* typeEnumStrings[];
int currentHeight = 0;

void read_from_TXT_file(GtkWidget *selectedPokemon) {
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

gboolean switch_screens(void) {
    if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == listScreen) {
        gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenIndicator), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(searchScreenIndicator), TRUE);
        gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(searchScreen));
        return TRUE;
    } 
    if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == searchScreen) {
        gtk_revealer_set_reveal_child(GTK_REVEALER(searchScreenIndicator), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenIndicator), TRUE);
        gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));
        // gtk_stack_set_visible_child(GTK_STACK(subStack),GTK_WIDGET(subEmptyScreen));
        // gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(infoEmptyScreen));
        return TRUE;
    }
    if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == pokemonImage) {
        gtk_revealer_set_reveal_child(GTK_REVEALER(displayScreenIndicator), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenIndicator), TRUE);
        gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));
        return TRUE;
    }
}

// Scrolls the list screen to best display selected, and surrounding, Pokemon.
// Future goals:
//  - Implement smooth scrolling (current code is very "snappy")
//  - Properly account for lower bound
//  - Gradient blur on bottom most visibile pokemon (This is more of a Glade/CSS
//    thing, but I think it's important to mention here)
gboolean scroll_list_screen(int pressedArrowKey) {
    GtkAdjustment *viewWindow = gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(viewBox));
    // 65362 is the int representation of the "Up-arrow Key"
    if (pressedArrowKey == 65362) {
        // Checks if current height allows up arrow to be pressed
        if (currentHeight >= 195) {
            // Moves screen up 
            currentHeight -= 65;
            gtk_adjustment_set_value(viewWindow, currentHeight - 130);
        }
    } else {
        // Checks if current height allows down arrow to be pressed
        if (currentHeight >= 130) {
            // Moves screen down
            currentHeight += 65;
            gtk_adjustment_set_value(viewWindow, currentHeight - 130);
        } else {
            // Increments current height by 65 pixels
            currentHeight += 65;
        }
    }
}

//KEYPRESS HANDLER- Treat each key as a function
gboolean keypress_function(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_Escape) {
        return switch_screens();
    }
    if (event->keyval == GDK_KEY_Down || event->keyval == GDK_KEY_Up) {
        scroll_list_screen(event->keyval);
    }
    if (event->keyval == GDK_KEY_g ) {
        printf("%s\n",gtk_widget_get_name(gtk_window_get_focus(GTK_WINDOW(mainWindow))));
    }
    if (event->keyval == GDK_KEY_b ) {
        sortPokemonList(0);
    }
    return FALSE;
}

int sortPokemonList(int orderMode) {
    printf("Function call works!\n");
}

// Handle logic in the main window
void handle_main_window(GtkButton *buttonClicked) {
    // Assemble path to pokemon image
    gtk_revealer_set_reveal_child(GTK_REVEALER(displayScreenIndicator), TRUE);
    gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenIndicator), FALSE);
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

    //TODO: This code should be reworked for i = 0 to be null
    // // Format pokemon first type from button label
    // gtk_label_set_text(GTK_LABEL(pokemonType1),typeEnumStrings[pokedexArray[selectedPokemon].firstType - 1]);

    // // Format pokemon second type
    // if (pokedexArray[selectedPokemon].secondType == 0) {
    //     gtk_label_set_text(GTK_LABEL(pokemonType2),"");
    // } else {
    //     gtk_label_set_text(GTK_LABEL(pokemonType2),typeEnumStrings[pokedexArray[selectedPokemon].secondType - 1]);
    // }

    //Switch sub window's focus to pokemon info
    gtk_stack_set_visible_child(GTK_STACK(subStack),GTK_WIDGET(dataScreen));
}

// Handle logic in 
void handle_info_window(GtkButton *buttonClicked) {
    gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(entryScreen));
    read_from_TXT_file(GTK_WIDGET(buttonClicked));
    gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), TRUE);
}

// Handle button presses
//TODO: Why is this an int?
// KNOWN_BUG
/* It's possible to click on another pokedex entry while the list screen is 
transitioning to the viewscreen. Look into preventing input until screen has
finished transitioning.*/
int pokemon_button_clicked (GtkButton *buttonClicked) {
    handle_main_window(buttonClicked);
    handle_sub_window(buttonClicked);
    handle_info_window(buttonClicked);
}

// Pokemon search handler
void search_pokemon(void) {
    int relevantPokemon = searchPokemonList(mainWindowButton,
                                            gtk_combo_box_get_active(GTK_COMBO_BOX(orderComboBox)),
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
int pokemon_search (GtkSearchEntry *entry, gpointer user_data) {
    search_pokemon();
}

int pokemon_spin_search (GtkSpinButton *entry, gpointer user_data) {
    search_pokemon();
}

void pokemon_range_search (GtkComboBox *widget, gpointer user_data) {
    search_pokemon();
}

void implement_CSS(void) {
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER (provider), 
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *cssFile = "buttonColors.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(cssFile), &error);
    g_object_unref(provider);
}


void generatePokedexButtons(void) {
    // Style Context variable needed to use CSS to style widgets
    GtkStyleContext   *context;

    // Null variable used to bypass having to pass data
    int *pInt = NULL; 

    // Variables unique to each button
    // TODO: Find a way to stop using magic numbers
    char buttonID[5];
    char nameString[10];
    char numberString[12];
    char iconString[10];
    char iconStringFromFile[30];
    char firstTypeString[20];
    char secondTypeString[20];
    char firstTypeCSS[20];
    char secondTypeCSS[20];
    char formattedPokedexNumber[10];
    char rawPokedexNumber[10];

    for (int i = 1; i <= 30; i++) {
        //// DEFINE UNIQUE IDENTIFIERS
        sprintf(buttonID,"%d",i); // Button ID
        sprintf(nameString,"name_%d",i); // Pokemon name
        sprintf(iconString,"icon_%d",i); // Pokemon icon
        sprintf(numberString,"number_%d",i); // Pokemon number

        // Pokemon icon location
        sprintf(iconStringFromFile,"assets/pokeSprites/icons/%d",i);
        strcat(iconStringFromFile,".png");

        // Pokemon number
        sprintf(formattedPokedexNumber, "%s","#");
        sprintf(rawPokedexNumber, "%03d", i);
        strcat(formattedPokedexNumber, rawPokedexNumber);

        // Pokemon types
        sprintf(firstTypeString,"type1_%d",i); // Pokemon icon
        sprintf(secondTypeString,"type2_%d",i); // Pokemon icon

        // Create string that formats types with CSS
        sprintf(firstTypeCSS, "%s", typeEnumStrings[pokedexArray[i-1].firstType]);
        strcat(firstTypeCSS, "_type");
        sprintf(secondTypeCSS, "%s", typeEnumStrings[pokedexArray[i-1].secondType]);
        strcat(secondTypeCSS, "_type");

        //// CREATE THE BUTTON
        mainWindowButton[i-1] = GTK_WIDGET(gtk_builder_get_object(builder, buttonID));

        //// FILL THE BUTTON WITH RELEVANT UNIQUE INFORMATION
        // Set icon image on button
        gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder, iconString)),
            iconStringFromFile);

        // Set Pokemon's name on button
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, nameString)),
            pokedexArray[i-1].name);

        // Set Pokemon's number on button
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, numberString)),
            formattedPokedexNumber);

        // Set Pokemon's first type...
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, firstTypeString)),
            typeEnumStrings[pokedexArray[i-1].firstType]);
        // Then apply the CSS to format it to the correct color
        context = gtk_widget_get_style_context(GTK_WIDGET(gtk_builder_get_object(builder, firstTypeString)));
        gtk_style_context_add_class(context, firstTypeCSS);

        // Set Pokemon's second type...
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, secondTypeString)),
            typeEnumStrings[pokedexArray[i-1].secondType]);
        // Then apply the CSS to format it to the correct color
        context = gtk_widget_get_style_context(GTK_WIDGET(gtk_builder_get_object(builder, secondTypeString)));
        gtk_style_context_add_class(context, secondTypeCSS);

        // Apply CSS to format button's color to allign with Pokemon's first type
        context = gtk_widget_get_style_context(GTK_WIDGET(gtk_builder_get_object(builder, buttonID)));
        gtk_style_context_add_class(context, typeEnumStrings[pokedexArray[i-1].firstType]);

        // Clicking the button will trigger the "pokemon_button_clicked" function
        g_signal_connect(GTK_BUTTON(mainWindowButton[i-1]), "clicked",
            G_CALLBACK(pokemon_button_clicked), pInt);

        // Finally, name the button to facilitate interaction with other functions
        gtk_widget_set_name(mainWindowButton[i-1],rawPokedexNumber);
    }
}