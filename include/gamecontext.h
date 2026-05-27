#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H
#include "common.h"
#include "constants.h"
#include "ecs/ecs.h"
#include "ecs/entity.h"
#include "input.h"
#include "leveldata.h"
typedef enum GhostMode
{
  GHOSTMODE_SCATTER,
  GHOSTMODE_CHASE,
  GHOSTMODE_FRIGHTENED,
  GHOSTMODE_EATEN_EYES,
  GHOSTMODE_IN_GHOSTHOUSE,
  GHOSTMODE_EXIT_GHOSTHOUSE
} GhostMode;
typedef struct GameContext
{
  Input input;
  LevelData levelData;
  Ghost ghostsEntities[GHOST_COUNT];
  int currentScore;
  int remainingPellets;
  bool isFrightenedGhostModeActive;
  bool isRoundWon;
  bool isGameOver;
  float frightenedGhostModeTimer;
  Entity playerEntity;
  GhostMode currentGhostMode;
  float ghostModeTimer;
  float deltaTime;
  int playerLives;
  // TODO: Add Audio, Graphics, and GameState
  // Audio audio;
  // GameState currentGameState;
  //  Graphics graphics;
} GameContext;
void CheckForRoundWon(GameContext *gameContext);
void InitializeGameContext(GameContext *gameContext);
void ReduceRemainingPellets(GameContext *gameContext);
void ResetPlayerPosition(GameContext *gameContext);
void TriggerFrightenedMode(GameContext *gameContext);
void TriggerGameOver(GameContext *gameContext);
void TriggerPlayerDeath(GameContext *gameContext);
void TriggerRoundWon(GameContext *gameContext);
void UpdateGhostTimer(GameContext *gameContext, float deltaTime);
#endif
