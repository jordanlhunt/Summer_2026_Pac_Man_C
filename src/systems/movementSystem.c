#include "../../include/systems/movementSystem.h"
void MovementSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  if (ECS_HasComponent(gameContext->playerEntity,
                       COMPONENT_POSITION | COMPONENT_VELOCITY) == false) {
    return;
  }
  Position *position = ECS_GetPosition(gameContext->playerEntity);
  Velocity *velocity = ECS_GetVelocity(gameContext->playerEntity);
  if (velocity->deltaRow == 0 && velocity->deltaColumn == 0) {
    return;
  }
  int targetRow = position->row + velocity->deltaRow;
  int targetColumn = position->column + velocity->deltaColumn;
  // Bounds Check
  if (targetRow < 0 || targetRow >= MAP_ROWS || targetColumn < 0 ||
      targetColumn < 0 || targetColumn >= MAP_COLUMNS) {
    return;
  }
  MapTile targetTile =
      GetMapTile(&gameContext->levelData, targetRow, targetColumn);
}
