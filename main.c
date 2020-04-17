#include "pokemonData.h"
#include "window_functions.h"

int main(int argc, char *argv[]) {
    // init GTK
    gtk_init(&argc, &argv);
    implement_CSS();

    // Build windows and connect signals described in Glade file
    builder = gtk_builder_new_from_file ("pokedex - new search.glade");
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
    for (int i = 1; i <= POKEDEX_SIZE; i++) {
        sprintf(str,"%d",i);
        mainWindowButton[i] = GTK_WIDGET(gtk_builder_get_object(builder, str));
        // GList *children = gtk_container_get_children(GTK_CONTAINER(mainWindowButton[i]));
        // PUT BUTTON PRESS EVENT HERE
    }

    viewBox = GTK_WIDGET(gtk_builder_get_object(builder, "viewBox"));

    mainStack = GTK_WIDGET(gtk_builder_get_object(builder, "mainStack"));
    searchScreen = GTK_WIDGET(gtk_builder_get_object(builder, "searchScreen"));
    listScreen = GTK_WIDGET(gtk_builder_get_object(builder, "listScreen"));
    pokemonImage = GTK_WIDGET(gtk_builder_get_object(builder, "pokemonImage"));

    // MAIN WINDOW --- SEARCH
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

    return EXIT_SUCCESS;
}