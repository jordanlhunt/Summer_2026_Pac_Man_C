#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H
#include "../include/map.h"
#include "common.h"
#include "ecs/ecs.h"
#include "ecs/entity.h"
#include "graphics.h"
#include "input.h"
#include "leveldata.h"
#define DOT_PELLET_SCORE_VALUE 1
#define POWER_PELLET_SCORE_VALUE 50
#define BASE_GHOST_SCORE 200
#define PLAYER_LIVES 3
#define FRIGHTEN_GHOST_MODE_DURATION 6.0f
#define CHASE_TIME_LIMIT 20.0f
#define SCATTER_TIME_LIMIT 7.0f

typedef struct GameContext {
  Input input;
  LevelData levelData;
  Entity ghostsEntities[GHOST_COUNT];
  int currentScore;
  int remainingPellets;
  int playerSpawnRow;
  int playerSpawnColumn;
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
