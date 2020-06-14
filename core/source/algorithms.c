#include "algorithms.h"

extern const char* evolutionEnumStrings[];
extern int currentHeight;

// Signal handlers
void pokemon_search(GtkWidget *entry, gpointer user_data) {
    char relevantPokemonString[25];

    int relevantPokemon = search_Pokemon_List(mainWindowButton,
        gtk_combo_box_get_active(GTK_COMBO_BOX(orderComboBox)),
        gtk_entry_get_text(GTK_ENTRY(pokemonNameSearchEntry)),
        gtk_spin_button_get_value(GTK_SPIN_BUTTON(pokemonHeightSpinButton)),
        gtk_combo_box_get_active(GTK_COMBO_BOX(heightComboBox)),
        gtk_spin_button_get_value(GTK_SPIN_BUTTON(pokemonWeightSpinButton)),
        gtk_combo_box_get_active(GTK_COMBO_BOX(weightComboBox)),
        gtk_combo_box_get_active(GTK_COMBO_BOX(pokemonFirstTypeSearch)),
        gtk_combo_box_get_active(GTK_COMBO_BOX(pokemonSecondTypeSearch)));

    sprintf(relevantPokemonString,"%d results(s) found", relevantPokemon);
    gtk_label_set_text(GTK_LABEL(pokemonResults), relevantPokemonString);

    // Resets scrollbar on list screen to zero
    currentHeight = 0;
    gtk_adjustment_set_value(viewWindow, currentHeight);
}

void generate_pokedex_buttons(void) {
    // Null variable used to bypass having to pass data
    int *pInt = NULL; 

    // Variables unique to each button
    char buttonID[5];
    char nameString[10];
    char numberString[12];
    char iconString[10];
    char iconStringFromFile[40];
    char firstTypeString[20];
    char secondTypeString[20];
    char firstTypeCSS[20];
    char secondTypeCSS[20];
    char formattedPokedexNumber[10];
    char rawPokedexNumber[10];

    for (int i = 1; i <= POKEDEX_SIZE; i++) {
        //// DEFINE UNIQUE IDENTIFIERS
        sprintf(buttonID,"%d",i); // Button ID
        sprintf(nameString,"name_%d",i); // Pokemon name
        sprintf(iconString,"icon_%d",i); // Pokemon icon
        sprintf(numberString,"number_%d",i); // Pokemon number

        // Pokemon icon location
        sprintf(iconStringFromFile,"assets/sprites/icons/%d.png",i);

        // Pokemon number
        sprintf(formattedPokedexNumber, "%s","#");
        sprintf(rawPokedexNumber, "%03d", i);
        strcat(formattedPokedexNumber, rawPokedexNumber);

        // Pokemon types
        sprintf(firstTypeString,"type1_%d",i); // Pokemon icon
        sprintf(secondTypeString,"type2_%d",i); // Pokemon icon

        // Create string that formats types with CSS
        sprintf(firstTypeCSS, "%s_type", typeEnumStrings[pokedexArray[i-1].firstType]);
        sprintf(secondTypeCSS, "%s_type", typeEnumStrings[pokedexArray[i-1].secondType]);

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
        style_given_element(firstTypeString,firstTypeCSS);

        // Set Pokemon's second type...
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, secondTypeString)),
            typeEnumStrings[pokedexArray[i-1].secondType]);
        // Then apply the CSS to format it to the correct color
        style_given_element(secondTypeString,secondTypeCSS);

        // Apply CSS to format button's color to allign with Pokemon's first type
        style_given_element(buttonID,
            typeEnumStrings[pokedexArray[i-1].firstType]);

        // Clicking the button will trigger the "pokemon_entry_clicked" function
        g_signal_connect(GTK_BUTTON(mainWindowButton[i-1]), "clicked",
            G_CALLBACK(pokemon_entry_clicked), pInt);

        // Finally, name the button to facilitate interaction with other functions
        gtk_widget_set_name(mainWindowButton[i-1],rawPokedexNumber);
    }
}

int fill_pokemon_evolution_entries(char *position, int counter, int threeTier) {
    char numberString[20];
    char imageString[20];
    char nameString[20];
    char cardString[20];
    char pokemonImageString[30];
    char formattedPokedexNumber[5];
    char rawPokedexNumber[5];
    char evolutionLevel[20];
    char screen[10];

    if (threeTier == 0) {
        sprintf(screen,"%s","two");
    } else {
        sprintf(screen,"%s","three");
    }

    sprintf(evolutionLevel, "Lvl. %d", pokedexArray[counter].level);
    sprintf(numberString, "%sTier_%sNumber", screen, position);
    sprintf(imageString, "%sTier_%sImage", screen, position);
    sprintf(nameString, "%sTier_%sName", screen, position);
    sprintf(cardString, "%sTierEvolution_%sCard", screen, position);

    sprintf(formattedPokedexNumber, "%s","#");
    sprintf(rawPokedexNumber, "%03d", pokedexArray[counter].number);
    strcat(formattedPokedexNumber, rawPokedexNumber);

    sprintf(pokemonImageString,"assets/sprites/main/%s.png",rawPokedexNumber);

    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, numberString)),
        formattedPokedexNumber);
    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder, imageString)),
        pokemonImageString);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, nameString)),
        pokedexArray[counter].name);

    style_evolution_card(cardString, typeEnumStrings[pokedexArray[counter].firstType]);

    if (position == "2nd") {
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "threeTier_1stEvolution")),
            evolutionLevel);
    }

    if (position == "3rd") {
        if (pokedexArray[counter].evolutionMethod > 1) {
            char pathToImage[40];
            sprintf(pathToImage, "assets/sprites/items/%s.png",
                evolutionEnumStrings[pokedexArray[counter].evolutionMethod - 2]);

            gtk_stack_set_visible_child(GTK_STACK(threeTier_evolutionSwitcher),
            threeTier_evolutionMethod);

            gtk_image_set_from_file(GTK_IMAGE(threeTier_evolutionMethod),
                pathToImage);
        } else {
            gtk_stack_set_visible_child(GTK_STACK(threeTier_evolutionSwitcher),
                threeTier_2ndEvolution);
            gtk_label_set_text(GTK_LABEL(threeTier_2ndEvolution),
                evolutionLevel);
        }
    }

    if (position == "2nd" && threeTier == 0) {
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "twoTier_1stEvolution")),
            evolutionLevel);
        if (pokedexArray[counter].evolutionMethod > 1) {
            char pathToImage[40];
            sprintf(pathToImage, "assets/sprites/items/%s.png",
                evolutionEnumStrings[pokedexArray[counter].evolutionMethod - 2]);

            gtk_stack_set_visible_child(GTK_STACK(twoTier_evolutionSwitcher),
                twoTier_evolutionMethod);

            gtk_image_set_from_file(GTK_IMAGE(twoTier_evolutionMethod),
                pathToImage);
        } else {
            gtk_stack_set_visible_child(GTK_STACK(twoTier_evolutionSwitcher),
                twoTier_1stEvolution);
            gtk_label_set_text(GTK_LABEL(twoTier_1stEvolution),
                evolutionLevel);
        }
    }
}

int find_evolutions(int selectedPokemon) {
    int adjustSelectedPokemon;

    // Have to do this because of pokemon sorting
    for (int i = 0; i < POKEDEX_SIZE; i++) {
        if (pokedexArray[i].number == selectedPokemon) {
            adjustSelectedPokemon = i;
        }
    }

    // Loop back to the selected pokemon's 1st stage
    if (pokedexArray[adjustSelectedPokemon].finalForm == TRUE || pokedexArray[adjustSelectedPokemon].evolvesFrom != NO_EVO) {
        pokemonStage += 1;
        for (int i=0;i<POKEDEX_SIZE;i++) {
            if (pokedexArray[i].number == pokedexArray[adjustSelectedPokemon].evolvesFrom) {
                // Uses recursion to accomplish the task!
                find_evolutions(pokedexArray[i].number);
            }
        }
    }

    // Go through the evolutionary stages
    if (pokedexArray[adjustSelectedPokemon].finalForm == FALSE && pokedexArray[adjustSelectedPokemon].evolvesFrom == NO_EVO) {
        //// printf("1st form: %s\n",pokedexArray[adjustSelectedPokemon].name);
        // Looks for 2nd evolutionary stage
        for (int j=0;j<POKEDEX_SIZE;j++) {
            if (pokedexArray[j].evolvesFrom == pokedexArray[adjustSelectedPokemon].number) {
                // Either goes on to look for 3rd evolutionary stage...
                if (pokedexArray[j].finalForm == FALSE) {
                    //// printf("2nd form: %s\n",pokedexArray[j].name);
                    for (int k=0;k<POKEDEX_SIZE;k++) {
                        //Finally, find the 3rd evolutionary stage
                        if (pokedexArray[k].evolvesFrom == pokedexArray[j].number) {
                            //// printf("3rd form (FINAL): %s\n\n",pokedexArray[k].name);
                            fill_pokemon_evolution_entries("1st",adjustSelectedPokemon,1);
                            fill_pokemon_evolution_entries("2nd",j,1);
                            fill_pokemon_evolution_entries("3rd",k,1);

                            godVar = 1;

                            currentlySelectedPokemon = pokemonStage;
                            pokemonStage = 0;
                        }
                    }
                // Or breaks out of loop if that's its final evolution
                } else {
                    //// printf("2nd form (FINAL): %s\n\n",pokedexArray[j].name);
                    fill_pokemon_evolution_entries("1st",adjustSelectedPokemon,0);
                    fill_pokemon_evolution_entries("2nd",j,0);

                    godVar = 0;

                    printf("Pokemon Stage: %d \n", pokemonStage);

                    currentlySelectedPokemon = pokemonStage;
                    pokemonStage = 0;
                }
            }
        }
    }
    // printf("Pokemon Stage: %d \n", pokemonStage);
}

// Searches Pokemon list for Pokemon who satisfy user-provided constraints
int search_Pokemon_List(GtkWidget** buttonArray,
                       int desiredOrder,
                       const char* name, 
                       float height, 
                       int greaterHeight,
                       float weight, 
                       int greaterWeight,
                       typeEnum firstType,
                       typeEnum secondType) {
  int i; // Loop Counter
  int j = 0; // Relevant Pokemon counter
  char *ptr1; // Name checker variable
  int ptr2, ptr3, ptr4, ptr5; // Height, weight, and types checker variables

  sort_pokedex_entries(desiredOrder);
  rearrange_buttons();

  for (i=0;i<POKEDEX_SIZE;i++) {
    // Check if Pokemon's name contains given string 
    ptr1 = strcasestr(pokedexArray[i].name,name);

    // Check if Pokemon's height falls within given range
    if (greaterHeight) {
      ptr2 = (pokedexArray[i].height >= height);
    } else {
      ptr2 = (pokedexArray[i].height <= height);
    }

    // Check if Pokemon's weight falls within given range
    if (greaterWeight) {
      ptr3 = (pokedexArray[i].weight >= weight);
    } else {
      ptr3 = (pokedexArray[i].weight <= weight);
    }

    // Check if Pokemon's first type matches with given first type
    if (firstType == NONE) {
      ptr4 = 1;
    } else {
      ptr4 = (pokedexArray[i].firstType == firstType);
    }

    // Check if Pokemon's second type matches with given second type
    if (secondType == NONE) {
      ptr5 = 1;
    } else {
      ptr5 = (pokedexArray[i].secondType == secondType);
    }

    // Determine whether the Pokemon satisfies all constraints
    if (ptr1 != NULL && ptr2 && ptr3 && ptr4 && ptr5) {
      j += 1;
      gtk_widget_show(buttonArray[pokedexArray[i].number -1]);
    } else {
      gtk_widget_hide(buttonArray[pokedexArray[i].number -1]);
    }
  }

  return j;
}

void set_pokemon_description_title(GtkWidget *buttonClicked) {
    int selectedPokemon = atoi(gtk_widget_get_name(GTK_WIDGET(buttonClicked))) - 1;
    char pokemonCategoryText[30];
    int adjustSelectedPokemon;

    // Have to do this because of pokemon sorting
    for (int i = 0; i < POKEDEX_SIZE; i++) {
        if (pokedexArray[i].number == selectedPokemon + 1) {
            adjustSelectedPokemon = i;
        }
    }

    gtk_label_set_text(GTK_LABEL(infoStackName), pokedexArray[adjustSelectedPokemon].name);

    sprintf(pokemonCategoryText, "The %s Pokemon",
        pokedexArray[adjustSelectedPokemon].category);
    gtk_label_set_text(GTK_LABEL(infoStackSpecies),pokemonCategoryText);

    style_evolution_card("infoStackBar", 
        typeEnumStrings[pokedexArray[adjustSelectedPokemon].firstType]);
}

// Sorting alogrithms
int sort_alphabetical(const void *a, const void *b) {
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;
    return strcmp(ia->name, ib->name);
}

int sort_numerical(const void *a, const void *b) { 
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;
    return ia->number - ib->number;
}

int sort_weight_ascending(const void *a, const void *b) { 
    int order;
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;

    if (ib->weight < ia->weight) {
        order = 1;
    } else if (ib->weight > ia->weight) {
        order = -1;
    } else {
        order = strcmp(ia->name, ib->name);
    }

    return order;
}

int sort_weight_descending(const void *a, const void *b) {
    int order;
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;

    if (ib->weight > ia->weight) {
        order = 1;
    } else if (ib->weight < ia->weight) {
        order = -1;
    } else {
        order = strcmp(ia->name, ib->name);
    }

    return order;
}

int sort_height_ascending(const void *a, const void *b) {
    int order;
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;

    if (ib->height < ia->height) {
        order = 1;
    } else if (ib->height > ia->height) {
        order = -1;
    } else {
        order = strcmp(ia->name, ib->name);
    }

    return order;
}

int sort_height_descending(const void *a, const void *b) { 
    int order;
    pokemon *ia = (pokemon *)a;
    pokemon *ib = (pokemon *)b;

    if (ib->height > ia->height) {
        order = 1;
    } else if (ib->height < ia->height) {
        order = -1;
    } else {
        order = strcmp(ib->name, ia->name);
    }

    return order;
}

// Select sorting algorithm
int sort_pokedex_entries(int sortingStyle) {
    size_t pokemon_len = sizeof(pokedexArray) / sizeof(struct pokemon);

    switch (sortingStyle) {
    case 0: // Numerical
        qsort(pokedexArray, pokemon_len, sizeof(pokemon), sort_numerical);
        break;

    case 1: // Alphabetical
        qsort(pokedexArray, pokemon_len, sizeof(pokemon), sort_alphabetical);
        break;

    case 2: // Heaviest
        qsort(pokedexArray, pokemon_len, sizeof(pokemon), sort_weight_descending);
        break;

    case 3: // Lightest
        qsort(pokedexArray, pokemon_len, sizeof(pokemon), sort_weight_ascending);
        break;

    case 4: // Tallest
        qsort(pokedexArray, pokemon_len, sizeof(pokemon), sort_height_descending);
        break;

    case 5: // Shortest
        qsort(pokedexArray, pokemon_len, sizeof(pokemon), sort_height_ascending);
        break;
    }
}

// Print sorted pokemon array
void print_pokemon_struct_array(struct pokemon *array, size_t len) { 
    size_t i;
 
    for(i=0; i<len; i++) 
        printf("--\n[ Name: %s \t Number: %d Height: %f Weight: %f ]\n", 
          array[i].name, array[i].number, array[i].height, array[i].weight);
 
    puts("--");
}


void rearrange_buttons(void) {
    size_t pokemon_len = sizeof(pokedexArray) / sizeof(struct pokemon);

    // print_pokemon_struct_array(pokedexArray, pokemon_len);

    for (int i = 0; i < POKEDEX_SIZE; i++) {
        gtk_box_reorder_child(GTK_BOX(pokemonEntryList), mainWindowButton[pokedexArray[i].number - 1], i);
    }
}