// map.h
#ifndef MAP_H
#define MAP_H
#include "common.h"
#include "ecs/ecs.h"
#include "graphics.h"
#include "leveldata.h"
#include "maptile.h"
#define PATH_TO_MAZE_FILE "./assets/maze.txt"
#define DOT_PELLET_SCORE_VALUE 1
#define POWER_PELLET_SCORE_VALUE 50
#define GHOST_SPEED 6.0f
#define GHOST_SPEED_EYES 12.0f
#define GHOST_SPEED_FRIGHTENED 5.0f

void LoadMap(LevelData *levelData, const char *filePath,
             Entity ghostEntities[]);
void DrawMap(LevelData *levelData, SDL_Renderer *renderer);
MapTile GetMapTile(LevelData *levelData, int row, int col);
void SetMapTile(LevelData *levelData, int row, int col, MapTile newTile);
#endif