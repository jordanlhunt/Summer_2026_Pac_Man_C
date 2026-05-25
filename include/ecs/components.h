// ecs/components.h
#ifndef COMPONENTS_H
#define COMPONENTS_H
typedef enum Direction { ZERO_DIRECTION, UP, DOWN, LEFT, RIGHT } Direction;
typedef struct Position {
  int row;
  int column;
} Position;
typedef struct Velocity {
  int deltaRow;
  int deltaColumn;
} Velocity;
typedef struct Renderable {
  int red;
  int green;
  int blue;
  int alpha;
  int width;
  int height;
} Renderable;
typedef struct PlayerControlled {
  Direction currentDirection;
} PlayerControlled;
typedef enum EdibleType {
  DOT,
  POWER_PELLET,
  FRUIT,
  FRIGHTENED_GHOST
} EdibleType;
typedef struct Edible {
  int scoreValue;
  EdibleType typeEaten;
} Edible;
typedef struct Active {
  bool isActive;
} Active;
typedef enum GhostType {
  GHOSTTYPE_BLINKY,
  GHOSTTYPE_PINKY,
  GHOSTTYPE_INKY,
  GHOSTTYPE_CLYDE
} GhostType;
typedef struct Ghost {
  GhostType ghostType;
  int scatterTargetRow;
  int scatterTargetColumn;
  Direction currentDirection;
} Ghost;
#endif
