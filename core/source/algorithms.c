#include "algorithms.h"

extern const char* evolutionEnumStrings[];
extern int currentHeight;

// Signal handlers
int fill_pokedex_array(void) {
    FILE *file;
    int count = 0;

    file = fopen("assets/files/csv/pokedex_entries.csv", "r");

    if (!file) {
        printf("Can't open file :(\n");
        return 1;
    }

    char *discovered = (char *) malloc(1);
    char *firstType = (char *) malloc(20);
    char *secondType = (char *) malloc(20);
    char *finalForm = (char *) malloc(1);
    char *evolutionMethod = (char *) malloc(15);

    // Grab line and add it to the array
    while (fscanf(file, " %[^,],%[^,],%[^,],%d,%[^,],%[^,],%f,%f,%[^,],%d,%[^,],%d,",
                                discovered,
                                pokedexEntries[count].name,
                                pokedexEntries[count].category,
                                &pokedexEntries[count].number,
                                firstType,
                                secondType,
                                &pokedexEntries[count].height,
                                &pokedexEntries[count].weight,
                                finalForm,
                                &pokedexEntries[count].evolvesFrom,
                                evolutionMethod,
                                &pokedexEntries[count].level) == 12) {

    // Handle discovered enum
    if (!strcmp(discovered,"FALSE")) {
        pokedexEntries[count].discovered = FALSE;
    } else {
        pokedexEntries[count].discovered = TRUE;
    }

    // Handle first type enum
    for(int i = 0; i < 17; ++i) {
        if(!strcmp(typeEnumStrings[i], firstType)) {
            pokedexEntries[count].firstType = i;
        }
    }

    // Handle second type enum
    for (int i = 0; i < 17; ++i) {
        if(!strcmp(typeEnumStrings[i], secondType)) {
            pokedexEntries[count].secondType = i;
        }
    }

    // Handle final form enum
    if (!strcmp(finalForm,"FALSE")) {
        pokedexEntries[count].finalForm = FALSE;
    } else {
        pokedexEntries[count].finalForm = TRUE;
    }

    // Handle evolution method enum
    for (int i = 0; i < 8; ++i) {
        if(!strcmp(evolutionEnumStrings[i], evolutionMethod)) {
            pokedexEntries[count].evolutionMethod = i;
        }
    }

    // printf("Discovered: %s\n", discovered);
    // printf("Name: %s\n", pokedexEntries[count].name);
    // printf("Species: %s\n", pokedexEntries[count].category);
    // printf("Number: %d\n", pokedexEntries[count].number);
    // printf("First type: %s\n", firstType);
    // printf("Second type: %s\n", secondType);
    // printf("Height: %f\n", pokedexEntries[count].height);
    // printf("Weight: %f\n", pokedexEntries[count].weight);
    // printf("Final form: %s\n", finalForm);
    // printf("Evolves from: %d\n", pokedexEntries[count].evolvesFrom);
    // printf("Evolution method: %s\n", evolutionMethod);
    // printf("Level: %d\n\n", pokedexEntries[count].level);

    count++;
                                }

    fclose(file);

    return 0;
}

void pokemon_search(GtkWidget *entry, gpointer user_data) {
    char relevantPokemonString[25];

    int relevantPokemon = search_pokemon_list(mainWindowButton,
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
    char formattedPokedexNumber[5];
    char rawPokedexNumber[10];

    for (int i = 1; i <= POKEDEX_SIZE; i++) {
        //// DEFINE UNIQUE IDENTIFIERS
        sprintf(buttonID,"%d",i); // Button ID
        sprintf(nameString,"name_%d",i); // Pokemon name
        sprintf(iconString,"icon_%d",i); // Pokemon icon
        sprintf(numberString,"number_%d",i); // Pokemon number

        // Pokemon number
        sprintf(formattedPokedexNumber, "%s","#");
        sprintf(rawPokedexNumber, "%03d", i);
        strcat(formattedPokedexNumber, rawPokedexNumber);

        // Pokemon types
        sprintf(firstTypeString,"type1_%d",i); // Pokemon icon
        sprintf(secondTypeString,"type2_%d",i); // Pokemon icon

        // Create string that formats types with CSS
        sprintf(firstTypeCSS, "%s_type", typeEnumStrings[pokedexEntries[i-1].firstType]);
        sprintf(secondTypeCSS, "%s_type", typeEnumStrings[pokedexEntries[i-1].secondType]);

        //// CREATE THE BUTTON
        mainWindowButton[i-1] = GTK_WIDGET(gtk_builder_get_object(builder, buttonID));

        // EMPTY POKEMON ENTRY
        if (pokedexEntries[i-1].discovered == TRUE) {
            // Pokemon icon location
            sprintf(iconStringFromFile,"assets/sprites/icons/%d.png",i);

            // Set Pokemon's name on button
            gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, nameString)),
                pokedexEntries[i-1].name);

            // Set Pokemon's first type...
            gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, firstTypeString)),
                typeEnumStrings[pokedexEntries[i-1].firstType]);
            // Then apply the CSS to format it to the correct color
            style_given_element(firstTypeString,firstTypeCSS);

            // Set Pokemon's second type...
            gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, secondTypeString)),
                typeEnumStrings[pokedexEntries[i-1].secondType]);
            // Then apply the CSS to format it to the correct color
            style_given_element(secondTypeString,secondTypeCSS);

            // Apply CSS to format button's color to allign with Pokemon's first type
            style_given_element(buttonID,
                typeEnumStrings[pokedexEntries[i-1].firstType]);

            // Clicking the button will trigger the "pokemon_entry_clicked" function
            g_signal_connect(GTK_BUTTON(mainWindowButton[i-1]), "clicked",
                G_CALLBACK(pokemon_entry_clicked), pInt);

        } else {
            sprintf(iconStringFromFile,"assets/sprites/icons/%s.png","???_1");
        }

        //// FILL THE BUTTON WITH RELEVANT UNIQUE INFORMATION
        // Set icon image on button
        gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder, iconString)),
            iconStringFromFile);

        // Set Pokemon's number on button
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, numberString)),
            formattedPokedexNumber);

        // Finally, name the button to facilitate interaction with other functions
        gtk_widget_set_name(mainWindowButton[i-1],rawPokedexNumber);
    }
}

int fill_pokemon_evolution_entries(char *position, int counter, int tier) {
    // Declare necessary variables
    char numberString[20];
    char imageString[20];
    char nameString[20];
    char cardString[20];
    char pokemonImageString[30];
    char pokemonNameString[10];
    char formattedPokedexNumber[5];
    char rawPokedexNumber[5];
    char evolutionLevel[20];
    char screen[10];

    // Determine how many stages the pokemon has
    switch (tier) {
        case 1:
            sprintf(screen,"%s","one");
            break;
        case 2:
            sprintf(screen,"%s","two");
            break;
        case 3:
            sprintf(screen,"%s","three");
            break;
    }

    sprintf(evolutionLevel, "Lvl. %d", pokedexEntries[counter].level);

    sprintf(numberString, "%sTier_%sNumber", screen, position);
    sprintf(imageString, "%sTier_%sImage", screen, position);
    sprintf(nameString, "%sTier_%sName", screen, position);
    sprintf(cardString, "%sTierEvolution_%sCard", screen, position);

    sprintf(formattedPokedexNumber, "%s","#");
    sprintf(rawPokedexNumber, "%03d", pokedexEntries[counter].number);
    strcat(formattedPokedexNumber, rawPokedexNumber);


    // Fill in pokemon card or leave it blank depending on whether the pokemon
    // has been discovered 
    if (pokedexEntries[counter].discovered == TRUE) {
        sprintf(pokemonImageString,"assets/sprites/main/%s.png",rawPokedexNumber);

        sprintf(pokemonNameString, "%s", pokedexEntries[counter].name);

        style_evolution_card(cardString, typeEnumStrings[pokedexEntries[counter].firstType]);
    } else {
        strcpy(pokemonImageString, "assets/sprites/main/100.png");

        // Needs a better name than Unknown due to it's similiarity with unown
        strcpy(pokemonNameString, "Unknown");

        // Need to remove CSS styling
    }

    // Fill in pokemon card information
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, nameString)),
       pokemonNameString);

    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder, imageString)),
        pokemonImageString);

    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, numberString)),
        formattedPokedexNumber);

    if (position == "2nd") {
        if (pokedexEntries[counter].discovered == TRUE) {
            gtk_label_set_text(GTK_LABEL(threeTier_1stEvolution),
                evolutionLevel);
        } else {
            gtk_label_set_text(GTK_LABEL(threeTier_1stEvolution),
                "???");
        }
    }

    if (position == "3rd") {
        if (pokedexEntries[counter].discovered == TRUE) {
            if (pokedexEntries[counter].evolutionMethod > 1) {
                char pathToImage[40];
                sprintf(pathToImage, "assets/sprites/items/%s.png",
                    evolutionEnumStrings[pokedexEntries[counter].evolutionMethod]);

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
        } else {
            gtk_label_set_text(GTK_LABEL(threeTier_2ndEvolution),
                "???");
        }
    }

    if (position == "2nd" && tier == 2) {
        if (pokedexEntries[counter].discovered == TRUE) {
            gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "twoTier_1stEvolution")),
                evolutionLevel);
            if (pokedexEntries[counter].evolutionMethod > 1) {
                char pathToImage[40];
                sprintf(pathToImage, "assets/sprites/items/%s.png",
                    evolutionEnumStrings[pokedexEntries[counter].evolutionMethod]);

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
        } else {
            gtk_label_set_text(GTK_LABEL(twoTier_1stEvolution),
                "???");
        }
    }
}

int find_evolutions(int selectedPokemon) {
    int adjustSelectedPokemon;

    // Have to do this because of pokemon sorting
    for (int i = 0; i < POKEDEX_SIZE; i++) {
        if (pokedexEntries[i].number == selectedPokemon) {
            adjustSelectedPokemon = i;
        }
    }

    // Loop back to the selected pokemon's 1st stage
    if (pokedexEntries[adjustSelectedPokemon].finalForm == TRUE || pokedexEntries[adjustSelectedPokemon].evolvesFrom != NO_EVO) {
        pokemonStage += 1;
        for (int i=0;i<POKEDEX_SIZE;i++) {
            if (pokedexEntries[i].number == pokedexEntries[adjustSelectedPokemon].evolvesFrom) {
                // Uses recursion to accomplish the task!
                find_evolutions(pokedexEntries[i].number);
            }
        }
    }

    // Go through the evolutionary stages
    if (pokedexEntries[adjustSelectedPokemon].finalForm == FALSE && pokedexEntries[adjustSelectedPokemon].evolvesFrom == NO_EVO) {
        // Looks for 2nd evolutionary stage
        for (int j = 0; j < POKEDEX_SIZE; j++) {
            if (pokedexEntries[j].evolvesFrom == pokedexEntries[adjustSelectedPokemon].number) {
                // Either goes on to look for 3rd evolutionary stage...
                if (pokedexEntries[j].finalForm == FALSE) {
                    for (int k = 0; k < POKEDEX_SIZE; k++) {
                        //Finally, find the 3rd evolutionary stage
                        if (pokedexEntries[k].evolvesFrom == pokedexEntries[j].number) {
                            fill_pokemon_evolution_entries("1st",adjustSelectedPokemon,3);
                            fill_pokemon_evolution_entries("2nd",j,3);
                            fill_pokemon_evolution_entries("3rd",k,3);

                            threeStagePokemon = 3; // Rename this variable maybe?

                            currentlySelectedPokemon = pokemonStage;
                            pokemonStage = 0;
                        }
                    }
                // Or breaks out of loop if that's its final evolution
                } else {
                    fill_pokemon_evolution_entries("1st",adjustSelectedPokemon,2);
                    fill_pokemon_evolution_entries("2nd",j,2);

                    threeStagePokemon = 2;

                    currentlySelectedPokemon = pokemonStage;
                    pokemonStage = 0;
                }
            }
        }
    }

    if (pokedexEntries[adjustSelectedPokemon].finalForm == TRUE &&
        pokedexEntries[adjustSelectedPokemon].evolvesFrom == NO_EVO) {
        fill_pokemon_evolution_entries("1st", adjustSelectedPokemon, 1);

        threeStagePokemon = 1;

        currentlySelectedPokemon = pokemonStage;
        pokemonStage = 0;
    }

}

// Searches Pokemon list for Pokemon who satisfy user-provided constraints
int search_pokemon_list(GtkWidget** buttonArray,
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
    ptr1 = strcasestr(pokedexEntries[i].name,name);

    // Check if Pokemon's height falls within given range
    if (greaterHeight) {
      ptr2 = (pokedexEntries[i].height >= height);
    } else {
      ptr2 = (pokedexEntries[i].height <= height);
    }

    // Check if Pokemon's weight falls within given range
    if (greaterWeight) {
      ptr3 = (pokedexEntries[i].weight >= weight);
    } else {
      ptr3 = (pokedexEntries[i].weight <= weight);
    }

    // Check if Pokemon's first type matches with given first type
    if (firstType == NONE) {
      ptr4 = 1;
    } else {
      ptr4 = (pokedexEntries[i].firstType == firstType);
    }

    // Check if Pokemon's second type matches with given second type
    if (secondType == NONE) {
      ptr5 = 1;
    } else {
      ptr5 = (pokedexEntries[i].secondType == secondType);
    }

    // Determine whether the Pokemon satisfies all constraints
    if (ptr1 != NULL && ptr2 && ptr3 && ptr4 && ptr5) {
      j += 1;
      gtk_widget_show(buttonArray[pokedexEntries[i].number -1]);
    } else {
      gtk_widget_hide(buttonArray[pokedexEntries[i].number -1]);
    }
  }

  return j;
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
    size_t pokemon_len = sizeof(pokedexEntries) / sizeof(struct pokemon);

    switch (sortingStyle) {
    case 0: // Numerical
        qsort(pokedexEntries, pokemon_len, sizeof(pokemon), sort_numerical);
        break;

    case 1: // Alphabetical
        qsort(pokedexEntries, pokemon_len, sizeof(pokemon), sort_alphabetical);
        break;

    case 2: // Heaviest
        qsort(pokedexEntries, pokemon_len, sizeof(pokemon), sort_weight_descending);
        break;

    case 3: // Lightest
        qsort(pokedexEntries, pokemon_len, sizeof(pokemon), sort_weight_ascending);
        break;

    case 4: // Tallest
        qsort(pokedexEntries, pokemon_len, sizeof(pokemon), sort_height_descending);
        break;

    case 5: // Shortest
        qsort(pokedexEntries, pokemon_len, sizeof(pokemon), sort_height_ascending);
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
    size_t pokemon_len = sizeof(pokedexEntries) / sizeof(struct pokemon);

    // print_pokemon_struct_array(pokedexEntries, pokemon_len);

    for (int i = 0; i < POKEDEX_SIZE; i++) {
        gtk_box_reorder_child(GTK_BOX(pokemonEntryList), mainWindowButton[pokedexEntries[i].number - 1], i);
    }
}

void populate_description_screen(int selectedPokemon) {
    int adjustSelectedPokemon;
    char formattedPokedexNumber[5];
    char rawPokedexNumber[5];
    char pokemonImageString[30];
    char pokemonCategoryText[40];
    char firstTypeCSS[20];
    char secondTypeCSS[20];

    // Have to do this because of pokemon sorting
    for (int i = 0; i < POKEDEX_SIZE; i++) {
        if (pokedexEntries[i].number == selectedPokemon) {
            adjustSelectedPokemon = i;
        }
    }

    // TODO: THIS IS USED PRETTY OFTEN, SHOULD PROBABLY TURN IT INTO IT'S OWN FUNCTION
    sprintf(formattedPokedexNumber, "%s","#");
    sprintf(rawPokedexNumber, "%03d", pokedexEntries[adjustSelectedPokemon].number);
    strcat(formattedPokedexNumber, rawPokedexNumber);
    // printf("%s\n", formattedPokedexNumber);

    // Populate number
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "descriptionScreen_Number")),
        formattedPokedexNumber);

    // Populate name
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "descriptionScreen_Name")),
        pokedexEntries[adjustSelectedPokemon].name);

    // Populate image
    sprintf(pokemonImageString,"assets/sprites/main/%s.png", rawPokedexNumber);
    gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder, "descriptionScreen_Image")),
        pokemonImageString);

    sprintf(pokemonCategoryText, "The %s Pokemon",
        pokedexEntries[adjustSelectedPokemon].category);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "descriptionScreen_Species")),
        pokemonCategoryText);

    // Set proper color
    // style_given_element("descriptionScreen_topArea",
    //     typeEnumStrings[pokedexEntries[selectedPokemon - 1].firstType]);
    overwrite_style_given_element("descriptionScreen_topArea",
        typeEnumStrings[pokedexEntries[adjustSelectedPokemon].firstType],
        typeEnumStrings, POKEMON_TYPES);

    // Populate description
    set_pokemon_description_text(GTK_WIDGET(gtk_builder_get_object(builder, "descriptionScreen_Text")));

    // TODO: Populate Height
    // TODO: Populate Weight
    /* These two things should be able to be converted between, and properly 
    diplayed in, metric and imperial. Not to forget that it should also display
    "Height: " and "Weight: ", respectively, before the relevant data. */

    sprintf(firstTypeCSS, "%s_type", typeEnumStrings[pokedexEntries[adjustSelectedPokemon].firstType]);
    sprintf(secondTypeCSS, "%s_type", typeEnumStrings[pokedexEntries[adjustSelectedPokemon].secondType]);

    // Set Pokemon's first type...
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "descriptionScreen_Type1")),
        typeEnumStrings[pokedexEntries[adjustSelectedPokemon].firstType]);

    // Then apply the CSS to format it to the correct color
    // style_pokemon_types("descriptionScreen_Type1", firstTypeCSS);
    // testVariable = strtok(firstTypeCSS, "_");
    // printf("%s\n", testVariable); //printing the token
    overwrite_style_given_element("descriptionScreen_Type1", firstTypeCSS,
        typeEnumStrings_CSS, POKEMON_TYPES);


    // Set Pokemon's second type...
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "descriptionScreen_Type2")),
        typeEnumStrings[pokedexEntries[adjustSelectedPokemon].secondType]);

    // Then apply the CSS to format it to the correct color
    overwrite_style_given_element("descriptionScreen_Type2", secondTypeCSS,
        typeEnumStrings_CSS, POKEMON_TYPES);
}