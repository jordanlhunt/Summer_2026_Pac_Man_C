#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H
#include "../../include/ecs/ecs.h"
#include "../../include/entityUtils.h"
#include "../../include/gamecontext.h"
#include "../../include/map.h"

void MovementSystem(struct GameContext *gameContext,
                    struct SDL_Renderer *renderer);
#endif
