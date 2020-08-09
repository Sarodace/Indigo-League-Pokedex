#include "gui.h"

// VARIABLES
// Declare global variables
extern const char* typeEnumStrings[];
extern int pokemonStage;

// FUNCTIONS
gboolean switch_screens(void) {
    // Switches to the search screen 
    if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == listScreen) {
        gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenRevealer), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(searchScreenRevealer), TRUE);
        gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(searchScreen));
        gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_Search));
        return TRUE;
    }
    // Switches to the list screen
    if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == searchScreen) {
        gtk_revealer_set_reveal_child(GTK_REVEALER(searchScreenRevealer), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenRevealer), TRUE);
        gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));
        gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_List));
        return TRUE;
    }
    // Switches to the list screen 
    if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == descriptionScreen) {
        gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenRevealer), FALSE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenRevealer), TRUE);
        gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));
        gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_List));
        return TRUE;
    }
}

// Scrolls the list screen to best display selected, and surrounding, Pokemon.
    // TODO: Implement smooth scrolling (current code is very "snappy")
    // TODO: Properly account for lower bound
    // TODO: Gradient blur on bottom most visibile pokemon (This is more of a Glade/CSS
    //    thing, but I think it's important to mention here)
gboolean scroll_list_screen(int pressedArrowKey) {
    // Checks if current is past a threshold and if up arrow key is pressed
    if (pressedArrowKey == GDK_KEY_Up && currentHeight >= 195) {
        currentHeight -= 65;
        gtk_adjustment_set_value(viewWindow, currentHeight - 130);
    }
    // Checks if down arrow key is pressed
    if (pressedArrowKey == GDK_KEY_Down) {
        // Move screen down if height is past a certain threshold
        if (currentHeight >= 130) {
            currentHeight += 65;
            gtk_adjustment_set_value(viewWindow, currentHeight - 130);
        // Increments current height by 65 pixels
        } else {
            currentHeight += 65;
        }
    }
}

/* This function is meant to handle all my key presses, but on second-thought
maybe individual functions would be better */
gboolean keypress_function(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    // Escape serves as the "back button", so it pretty much reverts the screen
    if (event->keyval == GDK_KEY_Escape) {
        return switch_screens();
    }

    // This would be so much better as a seperate function
    if (event->keyval == GDK_KEY_Down || event->keyval == GDK_KEY_Up) {
        scroll_list_screen(event->keyval);
    }

    if (event->keyval == GDK_KEY_Right) {
        // Determines which screen to transition to depending on the currently selected pokemon
        if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == descriptionScreen) {
            switch (threeStagePokemon) {
                // Transition to one stage screen for three stage pokemon
                case 1:
                    gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(oneTierScreen));
                    break;
                // Transition to two stage screen for two stage pokemon
                case 2:
                    gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(twoTierScreen));
                    break;
                // Transition to three stage screen for three stage pokemon
                case 3:
                    gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(threeTierScreen));
                    break;
            }

            // Change information displayed on top and bottom menus
            gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_Evolution));
            gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenRevealer), FALSE);
            gtk_revealer_set_reveal_child(GTK_REVEALER(evolutionScreenRevealer), TRUE);
        }
        // Allows for the right arrow key to be used to select a pokemon
        if (selectingPokemon == TRUE) {
            currentlySelectedPokemon = animate_pokemon_evolution_cards(currentlySelectedPokemon, event->keyval);
        }
    }

    if (event->keyval == GDK_KEY_Left) {
        // Check to see if not currently selecting pokemon
        if (selectingPokemon == FALSE) {
            // Checks if currently viewing pokemon evolutions
            if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == threeTierScreen ||
                gtk_stack_get_visible_child(GTK_STACK(mainStack)) == twoTierScreen ||
                gtk_stack_get_visible_child(GTK_STACK(mainStack)) == oneTierScreen) {

                gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(descriptionScreen));
                gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_Description));
                gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenRevealer), TRUE);
                gtk_revealer_set_reveal_child(GTK_REVEALER(evolutionScreenRevealer), FALSE);
            }
        }
        // Allows for the left arrow key to be used to select a pokemon
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

        if (gtk_stack_get_visible_child(GTK_STACK(mainStack)) == threeTierScreen) {
            if (selectingPokemon == TRUE) {
                unstyle_moving_evolution_card(relevantPokemonCard, "currently_selected");
                selectingPokemon = FALSE;
                printf("%s\n", relevantPokemonCard);
                return 0;
                // ADD CODE TO CHANGE CURRENTLY SELECTED POKEMON BASED ON WHAT IS CHOSEN IN THE EVOLUTION SCREEN
            }
            if (selectingPokemon == FALSE) {
                style_given_element(relevantPokemonCard, "currently_selected");
                selectingPokemon = TRUE;
                return 0;
            }
        }
    }
    return FALSE;
}


// Handle button presses
void pokemon_entry_clicked (GtkButton *buttonClicked) {
    // Change active icon on top menu bar
    gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenRevealer), FALSE);
    gtk_revealer_set_reveal_child(GTK_REVEALER(descriptionScreenRevealer), TRUE);

    // Change submenu bar to information for description screen
    gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_Description));

    // Autopopulate description screen
    populate_description_screen(atoi(gtk_widget_get_name(GTK_WIDGET(buttonClicked))));
    set_pokemon_description_text(GTK_WIDGET(buttonClicked));

    // Set evolution screen
    find_evolutions(atoi(gtk_widget_get_name(GTK_WIDGET(buttonClicked))));

    // Change screen to description screen
    gtk_stack_set_visible_child(GTK_STACK(mainStack), GTK_WIDGET(descriptionScreen));
}

// This function is a giant mess, I'll fix this in a future commit
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