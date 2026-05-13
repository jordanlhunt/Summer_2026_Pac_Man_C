#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H
#include "../../include/ecs/ecs.h"
#include "../../include/gamecontext.h"
#include "../../include/map.h"
typedef struct GameContext GameContext;
typedef struct SDL_Renderer SDL_Renderer;
void MovementSystem(GameContext *gameContext, SDL_Renderer *renderer);
#endif
