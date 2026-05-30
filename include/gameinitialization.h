#ifndef GAME_INITIALIZATION_H
#define GAME_INITIALIZATION_H
#include "../include/ecs/ecs.h"
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
typedef struct {
  SDL_Window *gameWindow;
  SDL_Renderer *renderer;
} SDLContext;

bool InitializeSDL(SDLContext *sdlContext);
bool InitializePlayer(GameContext *gameContext, Entity player);
void InitializeSystems();
bool InitializeGhosts(GameContext *gameContext);
void Shutdown(SDLContext *sdlContext);
#endif
