#include "../../include/xtreme.h"

Engine* engine_new(Window* window, unsigned int frames_per_second) {
    Engine* engine = malloc(sizeof(Engine));
    engine->window = window;
    engine->frames_per_second = frames_per_second;
    engine->delta_time = 1.0/engine->frames_per_second;
    engine->nodes = malloc(sizeof(Node*));
    engine->nodes_size = 0;
    engine->init = 0;
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

void engine_init_nodes(Node* node) {
    for (unsigned int index = 0; index < node->children_size; index++) {
	if (node->children[index]->init) {
	    node->children[index]->init(node->children[index]);
	}

	engine_init_nodes(node->children[index]);
    }
}

void engine_process_nodes(Node* node, float delta_time) {
    for (unsigned int index = 0; index < node->children_size; index++) {
	if (node->children[index]->process) {
	    node->children[index]->process(node->children[index], delta_time);
	}

	engine_process_nodes(node->children[index], delta_time);
    }
}

void engine_attach_methods(Engine* engine, void (*init)(Engine* self),
		           void (*process)(Engine* self), void (*draw)(Engine* self))
{
    engine->init = init;
    engine->process = process;
    engine->draw = draw;
}

void engine_run(Engine* engine) {
    InitWindow(engine->window->size.x, engine->window->size.y, engine->window->title);
    SetTargetFPS(engine->frames_per_second);
    engine->init(engine);

    for (unsigned int index = 0; index < engine->nodes_size; index++) {
	engine_init_nodes(engine->nodes[index]);
    }

    while (!WindowShouldClose()) {
	engine->process(engine);

	for (unsigned int index = 0; index < engine->nodes_size; index++) {
	    engine_process_nodes(engine->nodes[index], engine->delta_time);
	}

	BeginDrawing();
	ClearBackground(BLACK);
	engine->draw(engine);
	EndDrawing();
    }

    CloseWindow();
}
