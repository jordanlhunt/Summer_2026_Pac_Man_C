#ifndef MAP_H
#define MAP_H
#include "common.h"
#include "leveldata.h"
#include "maptile.h"
#include <SDL2/SDL_rect.h>
#include <stdio.h>
void LoadMap(LevelData *levelData, const char *filePath);
void DrawMap(LevelData *levelData, SDL_Renderer *renderer);
enum MapTile GetMapTile(LevelData *levelData, int row, int col);
void SetMapTile(LevelData *levelData, int row, int col, enum MapTile newTile);
#define NUMBER_OF_DOTS                                                         \
  222 // TODO: Fix the number of dots there should be 240 small dots and 4 power
      // pellets

#endif