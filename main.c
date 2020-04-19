#include "pokemonData.h"
#include "window_functions.h"

GtkStyleContext   *context;

int main(int argc, char *argv[]) {
    // init GTK
    gtk_init(&argc, &argv);
    implement_CSS();

    // Build windows and connect signals described in Glade file
    builder = gtk_builder_new_from_file ("pokedex - improved list.glade");
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    subWindow = GTK_WIDGET(gtk_builder_get_object(builder, "subWindow"));
    infoWindow = GTK_WIDGET(gtk_builder_get_object(builder, "infoWindow"));
    gtk_widget_add_events(mainWindow, GDK_KEY_PRESS_MASK);

    g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT (mainWindow), "key_press_event", G_CALLBACK (keypress_function), NULL);
    gtk_builder_connect_signals(builder, NULL);

    // Build widgets decribed in Glade file
    // MAIN WINDOW --- LIST
    char str[5];
    char nameString[10];
    char numberString[12];
    char iconString[10];
    char iconStringFromFile[30];
    char firstTypeString[19];
    char secondTypeString[19];

    char firstTypeCSS[20];
    char secondTypeCSS[20];


    char printvar[10];
    char test[10];


    for (int i = 1; i <= 30; i++) {
        sprintf(str,"%d",i); // Button ID
        sprintf(nameString,"name_%d",i); // Pokemon name
        sprintf(iconString,"icon_%d",i); // Pokemon icon
        sprintf(numberString,"number_%d",i); // Pokemon number

        // Pokemon icon location
        sprintf(iconStringFromFile,"assets/pokeSprites/icons/%d",i);
        strcat(iconStringFromFile,".png");

        // Pokemon number
        sprintf(printvar, "%s","#");
        sprintf(test, "%03d", i);
        strcat(printvar, test);

        // Pokemon types
        // printf("|%s|", buttonTypeText[pokedexArray[i-1].firstType]);
        // printf("|%s|\n", buttonTypeText[pokedexArray[i-1].secondType]);
        sprintf(firstTypeString,"type1_%d",i); // Pokemon icon
        sprintf(secondTypeString,"type2_%d",i); // Pokemon icon

        // Create string that formats types with CSS
        sprintf(firstTypeCSS, "%s", typeEnumStrings[pokedexArray[i-1].firstType]);
        strcat(firstTypeCSS, "_type");
        sprintf(secondTypeCSS, "%s", typeEnumStrings[pokedexArray[i-1].secondType]);
        strcat(secondTypeCSS, "_type");

        mainWindowButton[i-1] = GTK_WIDGET(gtk_builder_get_object(builder, str));

        // Set icon image on button
        gtk_image_set_from_file(GTK_IMAGE(gtk_builder_get_object(builder, iconString)),
            iconStringFromFile);

        // Set Pokemon's name on button
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, nameString)),
            pokedexArray[i-1].name);

        // Set Pokemon's number on button
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, numberString)),
            printvar);

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
        context = gtk_widget_get_style_context(GTK_WIDGET(gtk_builder_get_object(builder, str)));
        gtk_style_context_add_class(context, typeEnumStrings[pokedexArray[i-1].firstType]);
    }

    viewBox = GTK_WIDGET(gtk_builder_get_object(builder, "viewBox"));

    mainStack = GTK_WIDGET(gtk_builder_get_object(builder, "mainStack"));
    searchScreen = GTK_WIDGET(gtk_builder_get_object(builder, "searchScreen"));
    listScreen = GTK_WIDGET(gtk_builder_get_object(builder, "listScreen"));
    pokemonImage = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonImage"));

    // MAIN WINDOW --- SEARCH
    orderComboBox = GTK_WIDGET(gtk_builder_get_object(builder, "orderComboBox"));

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
    subEmptyScreen = GTK_WIDGET(gtk_builder_get_object(builder, "subEmptyScreen"));

    // INFO WINDOW
    infoStack = GTK_WIDGET(gtk_builder_get_object(builder, "infoStack"));
    entryScreen = GTK_WIDGET(gtk_builder_get_object(builder, "entryScreen"));
    infoEmptyScreen = GTK_WIDGET(gtk_builder_get_object(builder, "infoEmptyScreen"));

    // MENU BAR INDICATORS
    searchScreenIndicator = GTK_WIDGET(gtk_builder_get_object(builder, "searchScreenIndicator"));
    listScreenIndicator = GTK_WIDGET(gtk_builder_get_object(builder, "listScreenIndicator"));
    displayScreenIndicator = GTK_WIDGET(gtk_builder_get_object(builder, "displayScreenIndicator"));

    // Display the GUI
    gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));

    // gtk_label_set_line_wrap (GTK_LABEL(entryScreen),TRUE);
    // gtk_label_set_max_width_chars (GTK_LABEL (entryScreen), 30);
    // gtk_label_set_line_wrap_mode (GTK_LABEL (entryScreen),PANGO_WRAP_WORD);


    gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenIndicator), TRUE);
    gtk_widget_show(mainWindow);
    // gtk_widget_show(subWindow);
    // gtk_widget_show(infoWindow);
    gtk_main();
    // printf("%03d\n",2);
    // printf("%03d\n",92);
    // printf("%03d\n",134);

    return EXIT_SUCCESS;
}