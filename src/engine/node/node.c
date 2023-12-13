#include "../../../include/engine/node/node.h"
#include <malloc.h>
#include <string.h>

Node* node_new(Node* parent, const char* name, NodeKind kind) {
    Node* node = malloc(sizeof(Node));
    node->kind = kind;
    node->name = name;
    node->parent = parent;
    node->children = malloc(sizeof(Node*));
    node->children_size = 0;
    node->offset = parent ? parent->offset : (Vector2) {0, 0};
    node->size = (Vector2) {5, 5};
    node->rotation = 0;
    node->attributes = malloc(sizeof(Attribute*));
    node->attributes_size = 0;
    node->init = 0;
    node->process = 0;

    if (parent) {
	node_add_child(parent, node);
    }

    return node;
}

void node_attach_methods(Node* node, void (*init)(Node* self), void (*process)(Node* self, float delta_time)) {
    node->init = init;
    node->process = process;
}

void node_add_child(Node* node, Node* child) {
    node->children = realloc(node->children, (node->children_size + 1) * sizeof(Node*));
    node->children[node->children_size++] = child;
}

void node_remove_child(Node* node, const Node* child) {
    for (unsigned int index = 0; index < node->children_size; index++) {
	if (memcmp(node->children[index], child, sizeof(Node)) == 0) {
	    if (index) {
		for (unsigned int rest = index; rest < node->children_size; rest++) {
		    node->children[rest] = node->children[rest + 1];
		}
	    }

	    node->children_size--;
	}
    }
}

Node* node_get_child(const Node* node, const char* name) {
    for (unsigned int index = 0; index < node->children_size; index++) {
	if (memcmp(node->children[index]->name, name, strlen(node->children[index]->name)) == 0) {
	    return node->children[index];
	}
    }

    return 0;
}

void node_add_attribute(Node* node, Attribute* attribute) {
    if (node_get_attribute(node, attribute->name)) {
	return;
    }

    node->attributes = realloc(node->attributes, (node->attributes_size + 1) * sizeof(Attribute*));
    node->attributes[node->attributes_size++] = attribute;
}

void* node_get_attribute(const Node* node, const char* name) {
    for (unsigned int index = 0; index < node->attributes_size; index++) {
	if (memcmp(node->attributes[index]->name, name, strlen(node->attributes[index]->name)) == 0) {
	    return node->attributes[index]->value;
	}
    }

    return 0;
}

void node_set_attribute(Node* node, const char* name, void* value) {
    Attribute* attribute = node_get_attribute(node, name);
    attribute->value = value;
}
