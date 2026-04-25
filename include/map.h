#ifndef MAP_H
#define MAP_H
#include "common.h"
#include "gamecontext.h"
#include "leveldata.h"
#include "maptile.h"
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <string.h>
void LoadMap(LevelData *levelData, const char *filePath);
void DrawMap(LevelData *levelData, SDL_Renderer *renderer);
enum MapTile GetMapTile(LevelData *levelData, int x, int y);
#endif