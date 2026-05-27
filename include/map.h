// map.h
#ifndef MAP_H
#define MAP_H
#include "common.h"
#include "ecs/ecs.h"
#include "leveldata.h"
#include "maptile.h"
#define PATH_TO_MAZE_FILE "./assets/maze.txt"
void LoadMap(LevelData *levelData, const char *filePath);
void DrawMap(LevelData *levelData, SDL_Renderer *renderer);
MapTile GetMapTile(LevelData *levelData, int row, int col);
void SetMapTile(LevelData *levelData, int row, int col, MapTile newTile);
#endif