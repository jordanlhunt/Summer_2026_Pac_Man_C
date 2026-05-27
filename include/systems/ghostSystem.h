#ifndef GHOST_SYSTEM_H
#define GHOST_SYSTEM_H
#define INT_MAX 2147483647
#include "../../include/ecs/ecs.h"
#include "../../include/gamecontext.h"
#include "../../include/map.h"
#define GHOST_SPEED 6.0f
#define GHOST_SPEED_EYES 12.0f
#define GHOST_SPEED_FRIGHTENED 5.0f
void GhostSystem(GameContext *gameContext, SDL_Renderer *renderer);
#endif
