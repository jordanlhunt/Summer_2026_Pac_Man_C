#ifndef PLAYER_H
#define PLAYER_H
// Includes
#include "common.h"
#include "maptile.h"
// Forward Delectations
typedef struct SDL_Renderer SDL_Renderer;
typedef struct LevelData LevelData;
typedef struct GameContext GameContext;
typedef struct Player {
  int column;
  int row;
  int velocity;
} Player;
typedef struct PlayerMovementResult {
  bool didPlayerMove;
  int row;
  int column;
  MapTile collidedTile;
} PlayerMovementResult;
void InitializePlayer(GameContext *gameContext);
void DrawPlayer(GameContext *gameContext, SDL_Renderer *renderer);
void CollideWithDot(GameContext *gameContext, int row, int column,
                    MapTile collisionTile);
void CollideWithPowerPellet(GameContext *gameContext, int row, int column,
                            MapTile collisionTile);
PlayerMovementResult UpdatePlayer(GameContext *gameContext);
#endif