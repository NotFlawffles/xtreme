#include "../../include/xtreme.h"

Window* window_new(const char* title, Vector2 size, char configuration) {
    Window* window = malloc(sizeof(Window));
    window->title = title;
    window->size = size;
    window->configuration = configuration;
    return window;
}

Window* window_new_default(void) {
    return window_new(
	"Untitled",
	(Vector2) {512 * 16.0/9, 512},
	FLAG_VSYNC_HINT | FLAG_FULLSCREEN_MODE | FLAG_WINDOW_RESIZABLE |
	FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TRANSPARENT
    );
}

void window_set_position(Window* window, Vector2 position) {
    window->position = position;
    SetWindowPosition(window->position.x, window->position.y);
}

void window_set_size(Window* window, Vector2 size) {
    window->size.x = size.x;
    window->size.y = size.y;
    SetWindowSize(window->size.x, window->size.y);
}

void window_set_opacity(Window* window, float opacity) {
    window->opacity = opacity;
    SetWindowOpacity(window->opacity);
}
