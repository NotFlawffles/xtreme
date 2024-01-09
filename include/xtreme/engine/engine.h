#ifndef ENGINE_H
#define ENGINE_H

#include "window.h"
#include "../node/node.h"

typedef struct ENGINE {
    Window* window;
    unsigned int frames_per_second;
    float delta;
    Node** nodes;
    unsigned int nodes_size;

    void (*ready)(struct ENGINE* self);
    void (*process)(struct ENGINE* self, float delta);
    void (*draw)(struct ENGINE* self);
} Engine;

Engine* engine_new(Window* window, unsigned int frames_per_second);
void engine_add_root_node(Engine* engine, Node* node);
Node* engine_get_root_node(Engine* engine, const char* name);
void engine_ready_node(Node* node);
void engine_process_node(Node* node, float delta);

void engine_attach_methods(Engine* engine, void (*ready)(struct ENGINE* self),
		           void (*process)(struct ENGINE* self, float delta), void (*draw)(struct ENGINE* self));

void engine_run(Engine* engine);

#endif // ENGINE_H
