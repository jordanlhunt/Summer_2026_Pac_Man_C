#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H
#include "../../include/ecs/ecs.h"
#include "../../include/entityUtils.h"
#include "../../include/gamecontext.h"
#include "../../include/map.h"
#define TUNNEL_ROW 14
#define TUNNEL_ROW_LEFT_SIDE 0
#define TUNNEL_ROW_RIGHT_SIDE (MAP_COLUMNS - 1)
#define TILE_SIZE 1.0f
void MovementSystem(struct GameContext *gameContext,
                    struct SDL_Renderer *renderer);
#endif
