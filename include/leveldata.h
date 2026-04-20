#ifndef LEVELDATA_H
#define LEVELDATA_H
#include "map.h"
#include "maptile.h"
typedef struct {
  MapTile mapTiles[MAP_HEIGHT][MAP_WIDTH];
  bool isGameOver;
  int palletsRemaining;
} LevelData;
#endif