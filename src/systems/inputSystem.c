#include "../../include/systems/inputSystem.h"
#include <stdbool.h>

void InputSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  if (ECS_HasComponent(gameContext->playerEntity,
                       COMPONENT_PLAYER_CONTROLLED) == false) {
    return;
  }
  Velocity *velocity = ECS_GetVelocity(gameContext->playerEntity);
  velocity->deltaRow = 0;
  velocity->deltaColumn = 0;
  if (gameContext->input.moveUp) {
    velocity->deltaRow = -1;
  }
}
