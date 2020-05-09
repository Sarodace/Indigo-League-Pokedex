#include "css_styling.h"

// Evolution screen
GtkStyleContext   *twoTierEvolution_1stCardCSS;
GtkStyleContext   *twoTierEvolution_2ndCardCSS;

GtkStyleContext   *threeTierEvolution_1stCardCSS;
GtkStyleContext   *threeTierEvolution_2ndCardCSS;
GtkStyleContext   *threeTierEvolution_3rdCardCSS;

void style_given_element(const char* elementID, const char* cssTag) {
    GtkStyleContext   *context;

    context = gtk_widget_get_style_context(GTK_WIDGET(gtk_builder_get_object(builder, 
        elementID)));
    gtk_style_context_add_class(context, cssTag);
}

void style_evolution_card(const char* elementID, const char* cssTag) {
    GtkStyleContext   *context;
    context = gtk_widget_get_style_context(GTK_WIDGET(gtk_builder_get_object(builder, 
      elementID)));

    for (int i = 0; i < 17; i++) {
        printf("%s\n", typeEnumStrings[i]);
        if (gtk_style_context_has_class(context, typeEnumStrings[i])) {
            printf("Already has style class: %s\n", typeEnumStrings[i]);
            gtk_style_context_remove_class(context, typeEnumStrings[i]);
        }
    }

    gtk_style_context_add_class(context, cssTag);
}