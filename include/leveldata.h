#ifndef LEVELDATA_H
#define LEVELDATA_H
#define MAP_WIDTH 28
#define MAP_HEIGHT 31
#define MAP_GRID_CELL_SIZE 8
#include "maptile.h"
#include <stdbool.h>
typedef struct LevelData {
  enum MapTile mapTiles[MAP_WIDTH][MAP_HEIGHT];
  bool isGameOver;
  int palletsRemaining;
} LevelData;
#endif