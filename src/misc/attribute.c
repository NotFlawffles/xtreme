#include "../../include/xtreme.h"

Attribute* attribute_new(const char* name, void* value) {
    Attribute* attribute = malloc(sizeof(Attribute));
    attribute->name = name;
    attribute->value = value;
    return attribute;
}
