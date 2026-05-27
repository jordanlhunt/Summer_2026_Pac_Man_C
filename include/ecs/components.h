// ecs/components.h
#ifndef COMPONENTS_H
#define COMPONENTS_H

#define GHOST_COUNT 4
#define GHOST_HOUSE_ENTRANCE_ROW 11
#define GHOST_HOUSE_ENTRANCE_COLUMN 13
#define RELEASE_THRESHOLD_PINKY 0
#define RELEASE_THRESHOLD_INKY 30
#define RELEASE_THRESHOLD_CLYDE 90
typedef enum Direction
{
  ZERO_DIRECTION,
  UP,
  DOWN,
  LEFT,
  RIGHT
} Direction;
typedef struct Position
{
  int row;
  int column;
  float offsetX;
  float offsetY;
} Position;
typedef struct Velocity
{
  int deltaRow;
  int deltaColumn;
  float tilesPerSecond;
} Velocity;
typedef struct Renderable
{
  int red;
  int green;
  int blue;
  int alpha;
  int width;
  int height;
} Renderable;
typedef struct PlayerControlled
{
  Direction currentDirection;
} PlayerControlled;
typedef enum EdibleType
{
  DOT,
  POWER_PELLET,
  FRUIT,
  FRIGHTENED_GHOST
} EdibleType;
typedef struct Edible
{
  int scoreValue;
  EdibleType typeEaten;
} Edible;
typedef struct Active
{
  bool isActive;
} Active;
typedef enum GhostType
{
  GHOSTTYPE_BLINKY,
  GHOSTTYPE_PINKY,
  GHOSTTYPE_INKY,
  GHOSTTYPE_CLYDE
} GhostType;
typedef struct Ghost
{
  GhostType ghostType;
  int scatterTargetRow;
  int scatterTargetColumn;
  Direction currentDirection;
  int exitGhostHouseThreshold;
} Ghost;
#endif
