#ifndef PLAYER_H
#define PLAYER_H
// Includes
#include "common.h"
// Forward Delectations
typedef struct SDL_Renderer SDL_Renderer;
typedef struct LevelData LevelData;
typedef struct GameContext GameContext;
// Typedef
typedef struct Player {
  int column;
  int row;
  int velocity;
} Player;

void InitializePlayer(GameContext *gameContext);
void UpdatePlayer(GameContext *gameContext);
void DrawPlayer(GameContext *gameContext, SDL_Renderer *renderer);
#endif