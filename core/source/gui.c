#include "gui.h"

// PLAN IS TO COMBINE BOTH SCREENS INTO ONE

// VARIABLES
// Declare global variables
extern const char* typeEnumStrings[];

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
    if (pressedArrowKey == GDK_KEY_Up) {
        // Checks if current height allows up arrow to be pressed
        if (currentHeight >= 195) {
            // Moves screen up 
            currentHeight -= 65;
            gtk_adjustment_set_value(viewWindow, currentHeight - 130);
        }
    }
    if (pressedArrowKey == GDK_KEY_Down) {
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
        if (gtk_stack_get_visible_child(GTK_STACK(infoStack)) == threeTierEvolution ||
            gtk_stack_get_visible_child(GTK_STACK(infoStack)) == twoTierEvolution) {
            gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(descriptionScreen));
            gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), TRUE);
            gtk_revealer_set_reveal_child(GTK_REVEALER(evolutionScreenIndicator), FALSE);
        }
    }
    if (event->keyval == GDK_KEY_1) {
        printf("Description screen \n");
        gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(testScreen));
    }
    if (event->keyval == GDK_KEY_2) {
        printf("Evolution screen\n");
        gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(testScreenTwo));
    }
    if (event->keyval == GDK_KEY_Q) {
        printf("SPINNN\n");
        style_given_element("threeTierEvolution_Card1", "currently_selected");
    }

    if (event->keyval == GDK_KEY_8) {
        gtk_stack_set_visible_child(GTK_STACK(menuBarStack), GTK_WIDGET(displayScreenBar));
    }
    if (event->keyval == GDK_KEY_9) {
        gtk_stack_set_visible_child(GTK_STACK(menuBarStack), GTK_WIDGET(mainScreenBar));
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

    // // Select relevant pokemon and then switch to child
    // gtk_image_set_from_file(GTK_IMAGE(pokemonImage), selectedPokemon);
    // gtk_stack_set_visible_child(GTK_STACK(mainStack), GTK_WIDGET(pokemonImage));
    gtk_stack_set_visible_child(GTK_STACK(mainStack), GTK_WIDGET(testScreen));
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

// Handle logic in the info window
void handle_info_window(GtkButton *buttonClicked) {
    // Go to description screen
    gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(descriptionScreen));
    gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), TRUE);

    // Set relevant description screen text and title
    set_pokemon_description_text(GTK_WIDGET(buttonClicked));
    set_pokemon_description_title(GTK_WIDGET(buttonClicked));

    // Set evolution screen
    find_evolutions(atoi(gtk_widget_get_name(GTK_WIDGET(buttonClicked))));
}

// Handle button presses
void pokemon_entry_clicked (GtkButton *buttonClicked) {
    if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == listScreen) {
        handle_main_window(buttonClicked);
        handle_info_window(buttonClicked);
    }
}