#ifndef GAME_INITIALIZATION_H
#define GAME_INITIALIZATION_H
#include "../include/ecs/ecs.h"
#include "../include/graphics.h"
#include "../include/map.h"
#include "../include/systems/collisionSystem.h"
#include "../include/systems/ghostSystem.h"
#include "../include/systems/inputSystem.h"
#include "../include/systems/movementSystem.h"
#include "../include/systems/renderSystem.h"
#include "common.h"
#include "ecs/components.h"
#include "ecs/entity.h"
#include "gamecontext.h"
#define PLAYER_SPEED 7.0f
#define BLINKY_SPAWN_ROW 11
#define BLINKY_SPAWN_COLUMN 13
#define PINKY_SPAWN_ROW 13
#define PINKY_SPAWN_COLUMN 13
#define INKY_SPAWN_ROW 14
#define INKY_SPAWN_COLUMN 12
#define CLYDE_SPAWN_ROW 14
#define CLYDE_SPAWN_COLUMN 14
typedef struct {
  SDL_Window *gameWindow;
  SDL_Renderer *renderer;
} SDLContext;

bool InitializeSDL(SDLContext *sdlContext, GameContext *gameContext);
void Shutdown(SDLContext *sdlContext, GameContext *gameContext);
bool InitializePlayer(GameContext *gameContext, Entity player);
void InitializeSystems();

#endif
