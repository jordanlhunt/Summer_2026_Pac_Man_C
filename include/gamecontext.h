#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H
#include "common.h"
#include "entity.h"
#include "input.h"
#include "leveldata.h"
typedef struct Graphics Graphics;
typedef struct GameState GameState;
typedef struct Audio Audio;
typedef struct GameContext {
  //  Graphics graphics;
  Input input;
  LevelData levelData;
  Entity player;
  // Entity ghosts[4];
  // GameState currentGameState;
  // int currentScore;
  // Audio audio;
} GameContext;
#endif