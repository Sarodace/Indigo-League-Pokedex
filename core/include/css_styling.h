#ifndef CSS_STYLING_H
#define CSS_STYLING_H

#include "gui.h"

// FUNCTION PROTOTYPES
void style_given_element(const char* elementID, const char* cssTag);
void style_evolution_card(const char* elementID, const char* cssTag);

void overwrite_style_given_element(const char* elementID, const char* cssTag, const char** cssList, int cssList_size);

void unstyle_moving_evolution_card (const char* elementID, const char* cssTag);

#endif