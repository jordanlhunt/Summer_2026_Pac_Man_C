#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H
#include "common.h"
#include "ecs/entity.h"
#include "input.h"
#include "leveldata.h"
#include "map.h"
#include "maptile.h"
#define DOT_PELLET_SCORE_VALUE 1
#define FRIGHTEN_GHOST_MODE_DURATION 6.0f
#define NUMBER_OF_DOTS 244
#define POWER_PELLET_SCORE_VALUE 50
typedef struct GameContext {
  //  Graphics graphics;
  Input input;
  LevelData levelData;
  // Ghost ghostsEntities[4];
  // GameState currentGameState;
  int currentScore;
  int remainingPellets;
  bool isFrightenedGhostModeActive;
  bool isRoundWon;
  float frightenedGhostModeTimer;
  Entity playerEntity;
  // Audio audio;
} GameContext;

void HandlePlayerTileCollision(GameContext *gameContext, int row, int column,
                               MapTile collisionTile);
void TriggerFrightenedMode(GameContext *gameContext);
void TriggerRoundWon(GameContext *gameContext);
void ReduceRemainingPellets(GameContext *gameContext);
void CheckForRoundWon(GameContext *gameContext);
void InitializeGameContext(GameContext *gameContext);
#endif
