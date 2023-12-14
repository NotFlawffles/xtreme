#ifndef NODE_H
#define NODE_H

typedef enum {
    NodeScene,
    NodeArea,
    NodeCollision
} NodeKind;

typedef struct NODE {
    NodeKind kind;
    const char* name;
    struct NODE* parent;
    struct NODE** children;
    unsigned long children_size;
    Vector2 position;
    Vector2 size;
    float rotation;
    Attribute** attributes;
    unsigned long attributes_size;
    void (*init)(struct NODE* self);
    void (*process)(struct NODE* self, float delta_time);
} Node;

Node* node_new(Node* parent, const char* name, NodeKind kind);
Node* node_get_root_scene(Node* node);
void node_attach_position_to_root_scene(Node* node);
void node_attach_methods(Node* node, void (*init)(Node* self), void (*process)(Node* self, float delta_time));
void node_add_child(Node* node, Node* child);
void node_remove_child(Node* node, const Node* child);
Node* node_get_child(const Node* node, const char* name);

void node_add_attribute(Node* node, Attribute* attribute);
void* node_get_attribute(const Node* node, const char* name);
void node_set_attribute(Node* node, const char* name, void* value);

#endif // NODE_H
