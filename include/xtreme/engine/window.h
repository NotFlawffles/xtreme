#ifndef WINDOW_H
#define WINDOW_H

typedef struct {
    const char* title;
    Vector2 position;
    Vector2 size;
    float opacity;
    unsigned long configuration;
} Window;

Window* window_new(const char* title, Vector2 size, char configuration);
Window* window_new_default(void);
void window_set_position(Window* window, Vector2 position);
void window_set_size(Window* window, Vector2 size);
void window_set_opacity(Window* window, float opacity);

#endif // WINDOW_H
