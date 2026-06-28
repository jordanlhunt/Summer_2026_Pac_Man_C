#ifndef LEVELDATA_H
#define LEVELDATA_H
#define MAP_ROWS 31    // Y Dimension
#define MAP_COLUMNS 28 // X Dimension
#define MAP_GRID_CELL_SIZE 8
#define LOGICAL_WIDTH (MAP_COLUMNS * MAP_GRID_CELL_SIZE)
#define LOGICAL_HEIGHT (MAP_ROWS * MAP_GRID_CELL_SIZE)
#include "maptile.h"
#include <stdbool.h>
typedef struct LevelData {
  MapTile mapTiles[MAP_ROWS][MAP_COLUMNS];
  bool isGameOver;
} LevelData;
#endif
