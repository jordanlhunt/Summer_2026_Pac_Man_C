#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include "../../include/ecs/ecs.h"
#include "../../include/gamecontext.h"
void InputSystem(struct GameContext *gameContext,
                 struct SDL_Renderer *renderer);
#endif
