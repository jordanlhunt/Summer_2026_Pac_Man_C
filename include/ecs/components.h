// ecs/components.h
#ifndef COMPONENTS_H
#define COMPONENTS_H
typedef struct Position {
  int row;
  int column;
} Position;
typedef struct Velocity {
  int deltaRow;
  int deltaColumn;
  int speed;
} Velocity;
typedef struct Renderable {
  int red;
  int green;
  int blue;
  int alpha;
  int width, height;
} Renderable;
typedef struct PlayerControlled {
  bool isEnabled;
} PlayerControlled;
#endif
