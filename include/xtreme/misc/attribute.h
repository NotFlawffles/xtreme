#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

typedef struct {
    const char* name;
    void* value;
} Attribute;

Attribute* attribute_new(const char* name, void* value);

#endif // ATTRIBUTE_H
