#ifndef ENTITY_H
#define ENTITY_H
typedef enum { NONE, UP, DOWN, LEFT, RIGHT } Direction;
typedef struct {
  int x;
  int y;
  int velocity;
  int width;
  int height;
} Entity;
#endif