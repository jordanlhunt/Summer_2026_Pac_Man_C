#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include "../../include/ecs/ecs.h"
#include "../../include/gamecontext.h"
typedef struct GameContext GameContext;
typedef struct SDL_Renderer SDL_Renderer;
void InputSystem(GameContext *gameContext, SDL_Renderer *renderer);
#endif
