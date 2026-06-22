#ifndef GHOST_SYSTEM_H
#define GHOST_SYSTEM_H
#include "../../include/ecs/ecs.h"
#include "../../include/entityUtils.h"
#include "../../include/gamecontext.h"
#include "../../include/map.h"
#define CLYDE_RETREAT_THRESHOLD 64
void GhostSystem(GameContext *gameContext, SDL_Renderer *renderer);
#endif
