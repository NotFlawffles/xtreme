#include <xtreme.h>

const int WINDOW_SCALE = 512;
const float WINDOW_ASPECT_RATIO = 16.0/9;

// insanely big TODO: synchronize nodes with parents accordingely... lol

void left_paddle_init(Node* self) {
    int* speed = malloc(sizeof(int));
    *speed = 200;
    node_add_attribute(self, attribute_new("speed", speed));
}

void left_paddle_process(Node* self, float delta_time) {
    const int speed = *(int*) node_get_attribute(self, "speed");
    Node* area = node_get_child(self, "area");

    if (IsKeyDown(KEY_W)) {
	area->position.y -= speed * delta_time;
    } else if (IsKeyDown(KEY_S)) {
	area->position.y += speed * delta_time;
    }

    if (area->position.y <= 0) {
	area->position.y = 0;
    } else if (area->position.y + area->size.y >= self->parent->size.y) {
	area->position.y = self->parent->size.y - area->size.y;
    }
}

void right_paddle_init(Node* self) {
    int* speed = malloc(sizeof(int));
    *speed = 200;
    node_add_attribute(self, attribute_new("speed", speed));
}

void right_paddle_process(Node* self, float delta_time) {
    const int speed = *(int*) node_get_attribute(self, "speed");
    Node* area = node_get_child(self, "area");

    if (IsKeyDown(KEY_UP)) {
	area->position.y -= speed * delta_time;
    } else if (IsKeyDown(KEY_DOWN)) {
	area->position.y += speed * delta_time;
    }

    if (area->position.y <= 0) {
	area->position.y = 0;
    } else if (area->position.y + area->size.y >= self->parent->size.y) {
	area->position.y = self->parent->size.y - area->size.y;
    }
}

void left_paddle_area_init(Node* self) {
    self->size = (Vector2) {25, 100};
    self->position.x = 0;
    self->position.y = (self->parent->parent->size.y/2) - self->size.y/2;
}

void left_paddle_area_process(Node* self, float delta_time) {
    (void) self;
    (void) delta_time;
}

void right_paddle_area_init(Node* self) {
    self->size = (Vector2) {25, 100};
    self->position.x = self->parent->parent->size.x - self->size.x;
    self->position.y = (self->parent->parent->size.y/2) - self->size.y/2;
}

void right_paddle_area_process(Node* self, float delta_time) {
    (void) self;
    (void) delta_time;
}

void ball_area_init(Node* self) {
    self->size = (Vector2) {15, 15};
    self->position = (Vector2) {(self->parent->parent->size.x/2) - (self->size.x/2), (self->parent->parent->size.y/2) - (self->size.y/2)};
    Vector2* velocity = malloc(sizeof(Vector2));
    int* speed = malloc(sizeof(int));
    *velocity = (Vector2) {1, 1};
    *speed = 200;
    node_add_attribute(self, attribute_new("velocity", velocity));
    node_add_attribute(self, attribute_new("speed", speed));
}

void ball_area_process(Node* self, float delta_time) {
    Vector2* velocity = node_get_attribute(self, "velocity");
    const int speed = *(int*) node_get_attribute(self, "speed");
    Node* left_paddle = node_get_child(self->parent->parent, "left paddle");
    Node* left_paddle_area = node_get_child(left_paddle, "area");
    Node* right_paddle = node_get_child(self->parent->parent, "right paddle");
    Node* right_paddle_area = node_get_child(right_paddle, "area");

    if (self->position.y <= 0 || self->position.y >= self->parent->parent->size.y - self->size.y) {
	velocity->y *= -1;
    }

    if (CheckCollisionRecs((Rectangle) {left_paddle_area->position.x, left_paddle_area->position.y, left_paddle_area->size.x, left_paddle_area->size.y},
			   (Rectangle) {self->position.x, self->position.y, self->size.x, self->size.y}) ||

	CheckCollisionRecs((Rectangle) {right_paddle_area->position.x, right_paddle_area->position.y, right_paddle_area->size.x, right_paddle_area->size.y},
			   (Rectangle) {self->position.x, self->position.y, self->size.x, self->size.y}))
    {
	velocity->x *= -1;
    }

    self->position.x += velocity->x * speed * delta_time;
    self->position.y += velocity->y * speed * delta_time;
}

void init(Engine* self) {
    window_set_opacity(self->window, 0.9);

    Node* main = node_new(0, "main", NodeScene);
    main->size = self->window->size;

    Node* left_paddle = node_new(main, "left paddle", NodeScene);
    node_attach_methods(left_paddle, left_paddle_init, left_paddle_process);
    Node* left_paddle_area = node_new(left_paddle, "area", NodeArea);
    node_attach_methods(left_paddle_area, left_paddle_area_init, left_paddle_area_process);

    Node* right_paddle = node_new(main, "right paddle", NodeScene);
    node_attach_methods(right_paddle, right_paddle_init, right_paddle_process);
    Node* right_paddle_area = node_new(right_paddle, "area", NodeArea);
    node_attach_methods(right_paddle_area, right_paddle_area_init, right_paddle_area_process);

    Node* ball = node_new(main, "ball", NodeScene);
    Node* ball_area = node_new(ball, "area", NodeArea);
    node_attach_methods(ball_area, ball_area_init, ball_area_process);

    engine_add_root_node(self, main);
}

void process(Engine* self) {
    (void) self;
}

void draw(Engine* self) {
    Node* main = engine_get_root_node(self, "main");
    Node* left_paddle = node_get_child(main, "left paddle");
    Node* left_paddle_area = node_get_child(left_paddle, "area");
    Node* right_paddle = node_get_child(main, "right paddle");
    Node* right_paddle_area = node_get_child(right_paddle, "area");
    Node* ball = node_get_child(main, "ball");
    Node* ball_area = node_get_child(ball, "area");

    DrawText("XTreme Engine", (main->size.x/2) - 190, 10, 50, BLUE);
    DrawRectangleGradientV(left_paddle_area->position.x, left_paddle_area->position.y, left_paddle_area->size.x, left_paddle_area->size.y, RED, BLUE);
    DrawRectangleGradientV(right_paddle_area->position.x, right_paddle_area->position.y, right_paddle_area->size.x, right_paddle_area->size.y, RED, BLUE);
    DrawRectangle(ball_area->position.x, ball_area->position.y, ball_area->size.x, ball_area->size.y, BLUE);
}

int main(void) {
    Window* window = window_new(
	"Pong",
	(Vector2) {WINDOW_SCALE * WINDOW_ASPECT_RATIO, WINDOW_SCALE},
	FLAG_VSYNC_HINT | FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED
    );

    Engine* engine = engine_new(window, 60);
    engine_attach_methods(engine, init, process, draw);
    engine_run(engine);
}
