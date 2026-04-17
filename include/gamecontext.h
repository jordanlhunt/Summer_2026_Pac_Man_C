#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H
#include "common.h"
#include "input.h"
typedef struct Graphics Graphics;
typedef struct LevelData LevelData;
typedef struct Entity Entity;
typedef struct GameState GameState;
typedef struct Audio Audio;
typedef struct GameContext {
  Graphics graphics;
  Input input;
  LevelData levelData;
  Entity player;
  Entity ghosts[4];
  GameState currentGameState;
  int currentScore;
  Audio audio;
} GameContext;
#endif