#include "load_files.h"

void read_from_TXT_file(GtkWidget *selectedPokemon) {
    FILE* file = fopen("assets/files/txt/pokedex_entries.txt", "r");
    char line[256];
    int i = 0;

    while (fgets(line, sizeof(line), file)) {
        i++;
        if(i == atoi(gtk_widget_get_name(selectedPokemon))) {
            gtk_label_set_text(GTK_LABEL(entryScreen),line);
        }
    }
    fclose(file);
}

void implement_CSS(void) {
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER (provider), 
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *cssFile = "assets/files/css/buttonColors.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(cssFile), &error);
    g_object_unref(provider);
}