#include "../../include/systems/inputSystem.h"
// Turning for PAC-MAN is only allowed when centered on a given tile as
// described in dossier CH2_Cornering

void InputSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  (void)renderer;
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
  // Only consider turning when centered on a tile
  if (IsPlayerCentered(position) == false) {
    return;
  }
  if (gameContext->pendingDirection == ZERO_DIRECTION) {
    return;
  }

  if (gameContext->pendingDirection == UP) {
    requestedDeltaRow = -1;
  } else if (gameContext->pendingDirection == DOWN) {
    requestedDeltaRow = 1;
  } else if (gameContext->pendingDirection == LEFT) {
    requestedDeltaColumn = -1;
  } else if (gameContext->pendingDirection == RIGHT) {
    requestedDeltaColumn = 1;
  }
  // if no key is pressed exit function
  if (requestedDeltaColumn == 0 && requestedDeltaRow == 0) {
    return;
  }

  // check the next tile ahead is not a wall or a GHOSTDOOR
  int nextRow = position->row + requestedDeltaRow;
  int nextColumn = position->column + requestedDeltaColumn;
  MapTile nextTile = GetMapTile(&gameContext->levelData, nextRow, nextColumn);
  if (nextTile == TILE_WALL || nextTile == TILE_GHOST_DOOR) {
    return;
  }
  if (velocity->deltaRow == requestedDeltaRow &&
      velocity->deltaColumn == requestedDeltaColumn) {
    return;
  }
  // Safe to apply the input
  velocity->deltaColumn = requestedDeltaColumn;
  velocity->deltaRow = requestedDeltaRow;
  position->offsetX = 0.0f;
  position->offsetY = 0.0f;
}
