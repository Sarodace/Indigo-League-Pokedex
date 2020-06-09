#include "gui.h"
#include "load_files.h"
#include "pokemon_data.h"
#include "algorithms.h"
#include "css_styling.h"

// Test to see if logged into GitKraken

int main(int argc, char *argv[]) {
    // init GTK
    gtk_init(&argc, &argv);
    implement_CSS();

    // Build windows and connect signals described in Glade file
    builder = gtk_builder_new_from_file("assets/files/glade/pokedex - better evo.glade");
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    subWindow = GTK_WIDGET(gtk_builder_get_object(builder, "subWindow"));
    infoWindow = GTK_WIDGET(gtk_builder_get_object(builder, "infoWindow"));
    gtk_widget_add_events(mainWindow, GDK_KEY_PRESS_MASK);

    g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT (mainWindow), "key_press_event", G_CALLBACK (keypress_function), NULL);
    gtk_builder_connect_signals(builder, NULL);

    // MAIN WINDOW --- LIST
    viewBox = GTK_WIDGET(gtk_builder_get_object(builder, "viewBox"));
    pokemonEntryList = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonEntryList"));

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

    infoEmptyScreen = GTK_WIDGET(gtk_builder_get_object(builder, "infoEmptyScreen"));
    descriptionScreen = GTK_WIDGET(gtk_builder_get_object(builder, "descriptionScreen"));
    entryScreen = GTK_WIDGET(gtk_builder_get_object(builder, "entryScreen"));
    threeTierEvolution = GTK_WIDGET(gtk_builder_get_object(builder, "threeTierEvolution"));
    twoTierEvolution = GTK_WIDGET(gtk_builder_get_object(builder, "twoTierEvolution"));

    // MENU BAR INDICATORS
    searchScreenIndicator = GTK_WIDGET(gtk_builder_get_object(builder, "searchScreenIndicator"));
    listScreenIndicator = GTK_WIDGET(gtk_builder_get_object(builder, "listScreenIndicator"));
    displayScreenIndicator = GTK_WIDGET(gtk_builder_get_object(builder, "displayScreenIndicator"));

    // Info screen MENU BAR INDICATORS
    descriptionScreenIndicator = GTK_WIDGET(gtk_builder_get_object(builder, "descriptionScreenIndicator"));
    evolutionScreenIndicator = GTK_WIDGET(gtk_builder_get_object(builder, "evolutionScreenIndicator"));

    // Evolution screen
    threeTier_1stImage = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_1stImage"));
    threeTier_1stNumber = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_1stNumber"));
    threeTier_1stName = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_1stName"));
    threeTier_1stType1 = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_1stType1"));
    threeTier_1stType2 = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_1stType2"));

    threeTier_2ndImage = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_2ndImage"));
    threeTier_2ndNumber = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_2ndNumber"));
    threeTier_2ndName = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_2ndName"));
    threeTier_2ndType1 = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_2ndType1"));
    threeTier_2ndType2 = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_2ndType2"));

    threeTier_3rdImage = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_3rdImage"));
    threeTier_3rdNumber = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_3rdNumber"));
    threeTier_3rdName = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_3rdName"));
    threeTier_3rdType1 = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_3rdType1"));
    threeTier_3rdType2 = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_3rdType2"));

    threeTier_1stEvolution = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_1stEvolution"));
    threeTier_2ndEvolution = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_2ndEvolution"));


    twoTier_1stImage = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_1stImage"));
    twoTier_1stNumber = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_1stNumber"));
    twoTier_1stName = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_1stName"));
    twoTier_1stType1 = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_1stType1"));
    twoTier_1stType2 = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_1stType2"));

    twoTier_2ndImage = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_2ndImage"));
    twoTier_2ndNumber = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_2ndNumber"));
    twoTier_2ndName = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_2ndName"));
    twoTier_2ndType1 = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_2ndType1"));
    twoTier_2ndType2 = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_2ndType2"));

    twoTier_1stEvolution = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_1stEvolution"));


    twoTier_evolutionSwitcher = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_evolutionSwitcher"));
    twoTier_evolutionMethod = GTK_WIDGET(gtk_builder_get_object(builder, "twoTier_evolutionMethod"));

    threeTier_evolutionSwitcher = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_evolutionSwitcher"));
    threeTier_evolutionMethod = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_evolutionMethod"));


    testScreen = GTK_WIDGET(gtk_builder_get_object(builder, "testScreen"));
    testScreenTwo = GTK_WIDGET(gtk_builder_get_object(builder, "testScreenTwo"));

    menuBarStack = GTK_WIDGET(gtk_builder_get_object(builder, "menuBarStack"));
    mainScreenBar = GTK_WIDGET(gtk_builder_get_object(builder, "mainScreenBar"));
    displayScreenBar = GTK_WIDGET(gtk_builder_get_object(builder, "displayScreenBar"));

    viewWindow = gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(viewBox));


    // Infostack
    infoStackName = GTK_WIDGET(gtk_builder_get_object(builder, "infoStackName"));
    infoStackSpecies = GTK_WIDGET(gtk_builder_get_object(builder, "infoStackSpecies"));
    infoStackBar = GTK_WIDGET(gtk_builder_get_object(builder, "infoStackBar"));


    // Display the GUI
    gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));
    gtk_stack_set_visible_child(GTK_STACK(infoStack),GTK_WIDGET(infoEmptyScreen));

    // Build widgets decribed in Glade file
    generate_pokedex_buttons();

    gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenIndicator), TRUE);
    gtk_widget_show(mainWindow);
    // gtk_widget_show(subWindow);
    gtk_widget_show(infoWindow);
    gtk_main();

    return EXIT_SUCCESS;
}