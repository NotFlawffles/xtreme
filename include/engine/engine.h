#ifndef ENGINE_H
#define ENGINE_H

#include "window.h"
#include "node/node.h"

typedef struct ENGINE {
    Window* window;
    unsigned int frames_per_second;
    float delta_time;
    Node** nodes;
    unsigned int nodes_size;

    void (*init)(struct ENGINE* self);
    void (*process)(struct ENGINE* self);
    void (*draw)(struct ENGINE* self);
} Engine;

Engine* engine_new(Window* window, unsigned int frames_per_second);
void engine_add_node(Engine* engine, Node* node);
Node* engine_get_node(Engine* engine, const char* name);
void engine_init_nodes(Node* node);
void engine_process_nodes(Node* node, float delta_time);

void engine_attach_methods(Engine* engine, void (*init)(struct ENGINE* self),
		           void (*process)(struct ENGINE* self), void (*draw)(struct ENGINE* self));

void engine_run(Engine* engine);

#endif // ENGINE_H
