#include <malloc.h>
#include <string.h>
#include "../../../include/xtreme/engine/engine.h"

Engine* engine_new(Window* window, unsigned int frames_per_second) {
    Engine* engine = malloc(sizeof(Engine));
    engine->window = window;
    engine->frames_per_second = frames_per_second;
    engine->delta = 1.0/engine->frames_per_second;
    engine->nodes = malloc(sizeof(Node*));
    engine->nodes_size = 0;
    engine->ready = 0;
    engine->process = 0;
    engine->draw = 0;
    return engine;
}

void engine_add_root_node(Engine* engine, Node* node) {
    engine->nodes = realloc(engine->nodes, (engine->nodes_size + 1) * sizeof(Node*));
    engine->nodes[engine->nodes_size++] = node;
}

Node* engine_get_root_node(Engine* engine, const char* name) {
    for (unsigned int index = 0; index < engine->nodes_size; index++) {
	if (memcmp(engine->nodes[index]->name, name, strlen(engine->nodes[index]->name)) == 0) {
	    return engine->nodes[index];
	}
    }

    return 0;
}

void engine_ready_nodes(Node* node) {
    if (node->ready) {
	node->ready(node);
    }

    for (unsigned int index = 0; index < node->children_size; index++) {
	engine_ready_nodes(node->children[index]);
    }
}

void engine_process_nodes(Node* node, float delta) {
    if (node->process) {
	node->process(node, delta);
    }

    for (unsigned int index = 0; index < node->children_size; index++) {
	engine_process_nodes(node->children[index], delta);
    }
}

void engine_attach_methods(Engine* engine, void (*ready)(Engine* self),
		           void (*process)(Engine* self, float delta), void (*draw)(Engine* self))
{
    engine->ready = ready;
    engine->process = process;
    engine->draw = draw;
}

void engine_run(Engine* engine) {
    InitWindow(engine->window->size.x, engine->window->size.y, engine->window->title);
    SetTargetFPS(engine->frames_per_second);
    engine->ready(engine);

    for (unsigned int index = 0; index < engine->nodes_size; index++) {
	engine_ready_nodes(engine->nodes[index]);
    }

    while (!WindowShouldClose()) {
	engine->process(engine, engine->delta);

	for (unsigned int index = 0; index < engine->nodes_size; index++) {
	    engine_process_nodes(((Node*) engine->nodes[index]), engine->delta);
	}

	BeginDrawing();
	ClearBackground(BLACK);
	engine->draw(engine);
	EndDrawing();
    }

    CloseWindow();
}
