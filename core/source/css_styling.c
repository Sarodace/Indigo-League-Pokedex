#include "css_styling.h"

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
        if (gtk_style_context_has_class(context, typeEnumStrings[i])) {
            gtk_style_context_remove_class(context, typeEnumStrings[i]);
        }
    }

    gtk_style_context_add_class(context, cssTag);
}