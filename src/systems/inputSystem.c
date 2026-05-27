#include "../../include/systems/inputSystem.h"
// Turning for PAC-MAN is only allowed when centered on a given tile as
// described in dossier CH2_Cornering
static bool IsCenteredOnTile(Position *entityPosition) {
  // fabsf(float arg) find the absolute value of a floating point value
  bool isCentered = false;
  if (fabsf(entityPosition->offsetX) < TURN_TOLERANCE &&
      fabsf(entityPosition->offsetY) < TURN_TOLERANCE) {
    isCentered = true;
  }
  return isCentered;
}
void InputSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  if (!ECS_HasComponent(gameContext->playerEntity,
                        COMPONENT_PLAYER_CONTROLLED)) {
    printf(
        "[inputSystem.c] - player does not have player_controlled component\n");
    return;
  }
  if (!ECS_HasComponent(gameContext->playerEntity, COMPONENT_VELOCITY)) {
    printf("[inputSystem.c] - player does not have component velocity\n");
    return;
  }
  Position *position = ECS_GetPosition(gameContext->playerEntity);
  Velocity *velocity = ECS_GetVelocity(gameContext->playerEntity);
  int requestedDeltaRow = 0;
  int requestedDeltaColumn = 0;
  if (gameContext->input.moveUp) {
    requestedDeltaRow = -1;
  } else if (gameContext->input.moveDown) {
    requestedDeltaRow = 1;
  } else if (gameContext->input.moveLeft) {
    requestedDeltaColumn = -1;
  } else if (gameContext->input.moveRight) {
    requestedDeltaColumn = 1;
  }
  // if no key is pressed exit function
  if (requestedDeltaColumn == 0 && requestedDeltaRow == 0) {
    return;
  }
  if (IsCenteredOnTile(position) == false) {
    return;
  }
  // check the next tile ahead is not a wall or a GHOSTDOOR
  int nextRow = position->row + requestedDeltaRow;
  int nextColumn = position->column + requestedDeltaColumn;
  MapTile nextTile = GetMapTile(&gameContext->levelData, nextRow, nextColumn);
  if (nextTile == TILE_WALL || nextTile == TILE_GHOST_DOOR) {
    return;
  }
  // Safe to apply the input
  velocity->deltaColumn = requestedDeltaRow;
  velocity->deltaRow = requestedDeltaColumn;
  position->offsetX = 0.0f;
  position->offsetY = 0.0f;
}
