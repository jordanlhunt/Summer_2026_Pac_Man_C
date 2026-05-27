#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include "../../include/ecs/ecs.h"
#include "../../include/gamecontext.h"
#define TURN_TOLERANCE .15f
void InputSystem(struct GameContext *gameContext,
                 struct SDL_Renderer *renderer);
#endif
