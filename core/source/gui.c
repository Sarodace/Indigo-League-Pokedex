#include "gui.h"

// PLAN IS TO COMBINE BOTH SCREENS INTO ONE

// VARIABLES
// Declare global variables
extern const char* typeEnumStrings[];
extern int pokemonStage;

// FUNCTIONS
gboolean switch_screens(void) {
    if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == listScreen) {
        //// This is for the other menu bar apparently
        // gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), FALSE);
        // gtk_revealer_set_reveal_child(GTK_REVEALER(evolutionScreenIndicator), FALSE);

        // gtk_revealer_set_reveal_child(GTK_REVEALER(submenuBarRevealer), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenIndicator), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(searchScreenIndicator), TRUE);
        gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(searchScreen));
        gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_Search));
        return TRUE;
    } 
    if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == searchScreen) {
        gtk_revealer_set_reveal_child(GTK_REVEALER(searchScreenIndicator), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenIndicator), TRUE);
        gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));
        gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_List));
        return TRUE;
    }
    if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == testScreen) {
        gtk_revealer_set_reveal_child(GTK_REVEALER(displayScreenIndicator), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenIndicator), TRUE);
        gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));
        gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_List));
        gtk_stack_set_visible_child(GTK_STACK(menuBarStack),GTK_WIDGET(mainScreenBar));
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
        return switch_screens();
    }

    if (event->keyval == GDK_KEY_Down || event->keyval == GDK_KEY_Up) {
        scroll_list_screen(event->keyval);
    }

    if (event->keyval == GDK_KEY_Right) {
        if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == testScreen) {
            if (threeStagePokemon == TRUE) {
                gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(threeTierEvolution));
                gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(testScreenTwo));
            } else {
                gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(twoTierEvolution));
                gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(testScreenThree));
            }
            gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_Evos));
            gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), FALSE);
            gtk_revealer_set_reveal_child(GTK_REVEALER(evolutionScreenIndicator), TRUE);
        }
        if (selectingPokemon == TRUE) {
            currentlySelectedPokemon = animate_pokemon_evolution_cards(currentlySelectedPokemon, event->keyval);
        }
    }

    if (event->keyval == GDK_KEY_Left) {
        if (selectingPokemon == FALSE) {
            if (gtk_stack_get_visible_child(GTK_STACK(infoStack)) == threeTierEvolution ||
                gtk_stack_get_visible_child(GTK_STACK(infoStack)) == twoTierEvolution ||
                gtk_stack_get_visible_child(GTK_STACK(mainStack)) == testScreenTwo) {
                gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(testScreen));
                gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_Define));
                gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenIndicator), TRUE);
                gtk_revealer_set_reveal_child(GTK_REVEALER(evolutionScreenIndicator), FALSE);
            }
        }
        if (selectingPokemon == TRUE) {
            currentlySelectedPokemon = animate_pokemon_evolution_cards(currentlySelectedPokemon, event->keyval);
        }
    }

    if (event->keyval == GDK_KEY_space) {
        char relevantPokemonCard[30];

        /* Eventually will go back to this once I properly fix the definition
        styling function */
        // sprintf(relevantPokemonCard, "threeTierEvolution_Card%d", currentlySelectedPokemon);

        /* Temporary fix because this is a lot easier than changing a bunch of
        variable names :^) */
        switch (currentlySelectedPokemon) {
        case 0:
            sprintf(relevantPokemonCard, "threeTierEvolution_1stCard");
            break;
        case 1:
            sprintf(relevantPokemonCard, "threeTierEvolution_2ndCard");
            break;
        case 2:
            sprintf(relevantPokemonCard, "threeTierEvolution_3rdCard");
            break;
        }

        if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == testScreenTwo) {
            if (selectingPokemon == TRUE) {
                unstyle_moving_evolution_card(relevantPokemonCard, "currently_selected");
                selectingPokemon = FALSE;
                return 0;
            }
            if (selectingPokemon == FALSE) {
                style_given_element(relevantPokemonCard, "currently_selected");
                selectingPokemon = TRUE;
                return 0;
            }
        }
    }

    if (event->keyval == GDK_KEY_A) {
        printf("Before: %d\n", gtk_revealer_get_child_revealed(GTK_REVEALER(submenuBarRevealer)));
        gtk_revealer_set_reveal_child(GTK_REVEALER(submenuBarRevealer), TRUE);
        printf("After: %d\n", gtk_revealer_get_child_revealed(GTK_REVEALER(submenuBarRevealer)));
    }

    if (event->keyval == GDK_KEY_Z) {
        gtk_revealer_set_reveal_child(GTK_REVEALER(submenuBarRevealer), FALSE);
        printf("After: %d\n", gtk_revealer_get_child_revealed(GTK_REVEALER(submenuBarRevealer)));
        gtk_revealer_set_reveal_child(GTK_REVEALER(submenuBarRevealer), TRUE);
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
    // Change active icon on top menubar
    gtk_revealer_set_reveal_child(GTK_REVEALER(displayScreenIndicator), TRUE);
    gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenIndicator), FALSE);

    // Change information on the top and bottom menubars
    gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_Define));
    gtk_stack_set_visible_child(GTK_STACK(menuBarStack),GTK_WIDGET(displayScreenBar));

    // Change screen to description screen
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

int animate_pokemon_evolution_cards(int pokemonStage, int buttonPress) {
    char relevantPokemonCard[25];

    if (buttonPress == GDK_KEY_Left) {
        switch (pokemonStage) {
        case 0:
            return 0;
        // CASES 1 & 2 CAN BE COMPRESSED INTO ONE CASE
        case 1:
            // Unstyle currently hovering card
            unstyle_moving_evolution_card("threeTierEvolution_2ndCard", "currently_selected");

            // Style desired card to the left of it
            style_given_element("threeTierEvolution_1stCard", "currently_selected");
            return 0; // pokemonStage -= 1
        case 2:
            // Unstyle currently hovering card
            unstyle_moving_evolution_card("threeTierEvolution_3rdCard", "currently_selected");

            // Style desired card to the left of it
            style_given_element("threeTierEvolution_2ndCard", "currently_selected");
            return 1; // pokemonStage -= 1;
        }
    }
    if (buttonPress == GDK_KEY_Right) {
        switch (pokemonStage) {
        case 0:
            // Unstyle currently hovering card
            unstyle_moving_evolution_card("threeTierEvolution_1stCard", "currently_selected");

            // Style desired card to the left of it
            style_given_element("threeTierEvolution_2ndCard", "currently_selected");
            return 1; //pokemonStage += 1;
        case 1:
            // Unstyle currently hovering card
            unstyle_moving_evolution_card("threeTierEvolution_2ndCard", "currently_selected");

            // Style desired card to the left of it
            style_given_element("threeTierEvolution_3rdCard", "currently_selected");
            return 2; // pokemonStage += 1;
        case 2:
            return 2;
        }
    }
}