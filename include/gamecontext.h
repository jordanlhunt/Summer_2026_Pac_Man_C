#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H
#include "common.h"
#include "entity.h"
#include "input.h"
#include "leveldata.h"
#include "player.h"
#define DOT_PELLET_SCORE_VALUE 1
#define POWER_PELLET_SCORE_VALUE 50
#define FRIGHTEN_GHOST_MODE_DURATION 6.0f
typedef struct GameContext {
  //  Graphics graphics;
  Input input;
  LevelData levelData;
  Player player;
  // Ghost ghosts[4];
  // GameState currentGameState;
  int currentScore;
  int remainingPellets;
  bool isFrightenedGhostModeActive;
  bool isRoundWon;
  float frightenedGhostModeTimer;

  // Audio audio;
} GameContext;

void TriggerFrightenedMode(GameContext *gameContext);
void TriggerRoundWon(GameContext *gameContext);
void ReduceRemainingPellets(GameContext *gameContext);
void CheckForRoundWon(GameContext *gameContext);
#endif
