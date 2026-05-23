#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H
#include "common.h"
#include "constants.h"
#include "ecs/ecs.h"
#include "ecs/entity.h"
#include "input.h"
#include "leveldata.h"
typedef struct GameContext {
  //  Graphics graphics;
  Input input;
  LevelData levelData;
  Ghost ghostsEntities[4];
  // GameState currentGameState;
  int currentScore;
  int remainingPellets;
  bool isFrightenedGhostModeActive;
  bool isRoundWon;
  float frightenedGhostModeTimer;
  Entity playerEntity;
  // Audio audio;
} GameContext;
void TriggerFrightenedMode(GameContext *gameContext);
void TriggerRoundWon(GameContext *gameContext);
void ReduceRemainingPellets(GameContext *gameContext);
void CheckForRoundWon(GameContext *gameContext);
void InitializeGameContext(GameContext *gameContext);
#endif
