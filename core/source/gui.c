#include "gui.h"

// VARIABLES
// Declare global variables
extern const char* typeEnumStrings[];
int currentHeight = 0;

// FUNCTIONS
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
        //TODO MOVE INTO SWITCH SCREEN FUNCTION
        gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(evolutionScreenIndicator), FALSE);
        gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(infoEmptyScreen));
        return switch_screens();
    }
    if (event->keyval == GDK_KEY_Down || event->keyval == GDK_KEY_Up) {
        scroll_list_screen(event->keyval);
    }
    if (event->keyval == GDK_KEY_Right) {
        if (gtk_stack_get_visible_child(GTK_STACK(infoStack)) == descriptionScreen) {
            if (godVar == 1) {
                gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(threeTierEvolution));
            } else {
                gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(twoTierEvolution));
            }
            gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), FALSE);
            gtk_revealer_set_reveal_child(GTK_REVEALER(evolutionScreenIndicator), TRUE);
        }
    }
    if (event->keyval == GDK_KEY_Left) {
        if (gtk_stack_get_visible_child(GTK_STACK(infoStack)) == threeTierEvolution) {
            gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(descriptionScreen));
            gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), TRUE);
            gtk_revealer_set_reveal_child(GTK_REVEALER(evolutionScreenIndicator), FALSE);
        }
    }
    return FALSE;
}

// Handle logic in the main window
void handle_main_window(GtkButton *buttonClicked) {
    char selectedPokemon[40];

    // Assemble path to pokemon image
    gtk_revealer_set_reveal_child(GTK_REVEALER(displayScreenIndicator), TRUE);
    gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenIndicator), FALSE);
    sprintf(selectedPokemon, "assets/sprites/main/%s.png",
        gtk_widget_get_name(GTK_WIDGET(buttonClicked)));

    // Select relevent pokemon and then switch to child
    gtk_image_set_from_file(GTK_IMAGE(pokemonImage), selectedPokemon);
    gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(pokemonImage));
}

// Handle logic in the sub window
void handle_sub_window(GtkButton *buttonClicked) {
    char pokemonCategoryText[30];

    // Converts button's label to a number coinceding with that pokemon
    int selectedPokemon = atoi(gtk_widget_get_name(GTK_WIDGET(buttonClicked))) - 1;
    gtk_label_set_text(GTK_LABEL(pokemonName), pokedexArray[selectedPokemon].name);

    // Assemble pokemon category from button label
    sprintf(pokemonCategoryText, "The %s Pokemon",
        pokedexArray[selectedPokemon].category);
    gtk_label_set_text(GTK_LABEL(pokemonCategory),pokemonCategoryText);

    // Assemble pokedex number from button label
    char pokemonDexNumber[10] = "Dex: #";
    strcat(pokemonDexNumber, gtk_widget_get_name(GTK_WIDGET(buttonClicked)));
    gtk_label_set_text(GTK_LABEL(pokemonNumber),pokemonDexNumber);

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
    gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(descriptionScreen));
    read_from_TXT_file(GTK_WIDGET(buttonClicked));
    gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), TRUE);
}

// Handle button presses
//TODO: Why is this an int?
// KNOWN_BUG
/* It's possible to click on another pokedex entry while the list screen is 
transitioning to the viewscreen. Look into preventing input until screen has
finished transitioning.*/
int pokemon_entry_clicked (GtkButton *buttonClicked) {
    handle_main_window(buttonClicked);
    handle_sub_window(buttonClicked);
    handle_info_window(buttonClicked);
    find_evolutions(atoi(gtk_widget_get_name(GTK_WIDGET(buttonClicked))));
    printf("________________\n");
}