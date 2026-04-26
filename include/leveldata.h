#ifndef LEVELDATA_H
#define LEVELDATA_H
#define MAP_ROWS 31    // Y Dimension
#define MAP_COLUMNS 28 // X Dimension
#define MAP_GRID_CELL_SIZE 8
#include "maptile.h"
#include <stdbool.h>
typedef struct LevelData {
  enum MapTile mapTiles[MAP_ROWS][MAP_COLUMNS];
  bool isGameOver;
  int palletsRemaining;
} LevelData;
#endif