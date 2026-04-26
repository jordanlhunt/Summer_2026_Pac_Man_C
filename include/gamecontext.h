#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H
#include "common.h"
#include "entity.h"
#include "input.h"
#include "leveldata.h"
#include "player.h"
typedef struct GameContext {
  //  Graphics graphics;
  Input input;
  LevelData levelData;
  Player player;
  // Entity ghosts[4];
  // GameState currentGameState;
  // int currentScore;
  // Audio audio;
} GameContext;
#endif