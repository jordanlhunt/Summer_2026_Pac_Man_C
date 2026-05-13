// ecs/components.h
#ifndef COMPONENTS_H
#define COMPONENTS_H
typedef struct Position {
  int x;
  int y;
} Position;
typedef struct Velocity {
  int deltaX;
  int deltaY;
} Velocity;
typedef struct Renderable {
  int red;
  int green;
  int blue;
  int alpha;
  int width, height;
} Renderable;
typedef struct PlayerControlled {
  int dummy;
} PlayerControlled;
#endif