#include "gui.h"
#include "load_files.h"
#include "pokemon_data.h"
#include "algorithms.h"
#include "css_styling.h"

int main(int argc, char *argv[]) {
    // initialize GTK
    gtk_init(&argc, &argv);
    implement_CSS();

    // Construct main window
    builder = gtk_builder_new_from_file("assets/files/glade/pokedex layout.glade");
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    gtk_widget_add_events(mainWindow, GDK_KEY_PRESS_MASK);

    // Connect signals
    g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT (mainWindow), "key_press_event", G_CALLBACK (keypress_function), NULL);
    gtk_builder_connect_signals(builder, NULL);

    /// VARIABLES
    mainStack = GTK_WIDGET(gtk_builder_get_object(builder, "mainStack"));

    // Search screen variables
    searchScreen = GTK_WIDGET(gtk_builder_get_object(builder, "searchScreen"));

    orderComboBox = GTK_WIDGET(gtk_builder_get_object(builder, "orderComboBox"));
    pokemonNameSearchEntry = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonNameSearchEntry"));
    pokemonFirstTypeSearch = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonFirstTypeSearch"));
    pokemonSecondTypeSearch = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonSecondTypeSearch"));
    weightComboBox = GTK_WIDGET(gtk_builder_get_object(builder, "weightComboBox"));
    pokemonWeightSpinButton = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonWeightSpinButton"));
    heightComboBox = GTK_WIDGET(gtk_builder_get_object(builder, "heightComboBox"));
    pokemonHeightSpinButton = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonHeightSpinButton"));
    pokemonResults = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonResults"));

    // List screen variables
    listScreen = GTK_WIDGET(gtk_builder_get_object(builder, "listScreen"));
    viewBox = GTK_WIDGET(gtk_builder_get_object(builder, "viewBox"));
    pokemonEntryList = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonEntryList"));

    // Decription screen variables
    descriptionScreen = GTK_WIDGET(gtk_builder_get_object(builder, "descriptionScreen"));

    // Three-tier screen variables
    threeTierScreen = GTK_WIDGET(gtk_builder_get_object(builder, "threeTierScreen"));

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
    threeTier_evolutionSwitcher = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_evolutionSwitcher"));
    threeTier_evolutionMethod = GTK_WIDGET(gtk_builder_get_object(builder, "threeTier_evolutionMethod"));

    // Two-tier screen variables
    twoTierScreen = GTK_WIDGET(gtk_builder_get_object(builder, "twoTierScreen"));

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

    // Menu bar
    searchScreenRevealer = GTK_WIDGET(gtk_builder_get_object(builder, "searchScreenRevealer"));
    listScreenRevealer = GTK_WIDGET(gtk_builder_get_object(builder, "listScreenRevealer"));
    descriptionScreenRevealer = GTK_WIDGET(gtk_builder_get_object(builder, "descriptionScreenRevealer"));
    evolutionScreenRevealer = GTK_WIDGET(gtk_builder_get_object(builder, "evolutionScreenRevealer"));

    // Submenu bar
    submenuBarStack = GTK_WIDGET(gtk_builder_get_object(builder, "submenuBarStack"));
    submenuBarStack_Search = GTK_WIDGET(gtk_builder_get_object(builder, "submenuBarStack_Search"));
    submenuBarStack_List = GTK_WIDGET(gtk_builder_get_object(builder, "submenuBarStack_List"));
    submenuBarStack_Description = GTK_WIDGET(gtk_builder_get_object(builder, "submenuBarStack_Description"));
    submenuBarStack_Evolution = GTK_WIDGET(gtk_builder_get_object(builder, "submenuBarStack_Evolution"));

    viewWindow = gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(viewBox));

    // Populate pokemon entry buttons
    generate_pokedex_buttons();

    // Display the GUI
    gtk_stack_set_visible_child(GTK_STACK(mainStack),GTK_WIDGET(listScreen));
    gtk_stack_set_visible_child(GTK_STACK(submenuBarStack),GTK_WIDGET(submenuBarStack_List));
    gtk_revealer_set_reveal_child(GTK_REVEALER(listScreenRevealer), TRUE);
    gtk_widget_show(mainWindow);
    gtk_main();

    return EXIT_SUCCESS;
}