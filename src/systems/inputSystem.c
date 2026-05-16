#include "../../include/systems/inputSystem.h"

void InputSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  if (ECS_HasComponent(gameContext->playerEntity,
                       COMPONENT_PLAYER_CONTROLLED) == false) {
    printf(
        "[inputSystem.c] - player does not have player_controlled component\n");
    return;
  }
  if (ECS_HasComponent(gameContext->playerEntity, COMPONENT_VELOCITY)) {
    printf("[inputSystem.c] - player does not have component velocity\n");
    return;
  }
  Velocity *velocity = ECS_GetVelocity(gameContext->playerEntity);
  velocity->deltaRow = 0;
  velocity->deltaColumn = 0;
  if (gameContext->input.moveUp) {
    velocity->deltaRow = -1;
  } else if (gameContext->input.moveDown) {
    velocity->deltaRow = 1;
  } else if (gameContext->input.moveLeft) {
    velocity->deltaColumn = -1;
  } else if (gameContext->input.moveRight) {
    velocity->deltaColumn = 1;
  }
}
