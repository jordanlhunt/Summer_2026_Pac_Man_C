#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H
#include "../include/map.h"
#include "audio.h"
#include "common.h"
#include "ecs/ecs.h"
#include "ecs/entity.h"
#include "gamestate.h"
#include "graphics.h"
#include "input.h"
#include "leveldata.h"
#define HIGH_SCORE_SAVE_FILE "highscore.dat"
#define DOT_PELLET_SCORE_VALUE 1
#define POWER_PELLET_SCORE_VALUE 50
#define BASE_GHOST_SCORE 200
#define BASE_FRUIT_SCORE 100
#define PLAYER_LIVES 3
#define FRIGHTEN_GHOST_MODE_DURATION 6.0f
#define CHASE_TIME_LIMIT 20.0f
#define SCATTER_TIME_LIMIT 7.0f
#define FRUIT_SPAWN_1 70
#define FRUIT_SPAWN_2 170
#define FRUIT_DURATION 9.0f

typedef struct GameContext {
  AudioState audioPlayer;
  bool isFrightenedGhostModeActive;
  bool isGameOver;
  bool isRoundWon;
  Direction pendingDirection;
  Entity ghostsEntities[GHOST_COUNT];
  Entity playerEntity;
  Entity fruitEntity;
  float fruitTimer;
  float deltaTime;
  float frightenedGhostModeTimer;
  float ghostModeTimer;
  GameState currentGameState;
  GhostMode currentGhostMode;
  Input input;
  int currentScore;
  int highScore;
  int playerLives;
  int playerSpawnColumn;
  int playerSpawnRow;
  int remainingPellets;
  LevelData levelData;

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
void UpdateFruitTimer(GameContext *gameContext, float deltaTime);
void ResetGameRound(GameContext *gameContext);

#endif
