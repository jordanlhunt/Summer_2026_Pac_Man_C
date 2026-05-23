#include "../../include/systems/movementSystem.h"
void MovementSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  int activeEntitieCount = ECS_GetActiveEntitiesCount();
  for (int i = 0; i < activeEntitieCount; i++) {
    Entity activeEntity = ECS_GetActiveEntity(i);
    if (ECS_HasComponents(activeEntity,
                          COMPONENT_POSITION | COMPONENT_VELOCITY) == false) {
      continue;
    }
    Position *position = ECS_GetPosition(activeEntity);
    Velocity *velocity = ECS_GetVelocity(activeEntity);
    if (velocity->deltaRow == 0 && velocity->deltaColumn == 0) {
      continue;
    }
    int targetRow = position->row + velocity->deltaRow;
    int targetColumn = position->column + velocity->deltaColumn;
    // Bounds Check
    if (targetRow < 0 || targetRow >= MAP_ROWS || targetColumn < 0 ||
        targetColumn >= MAP_COLUMNS) {
      continue;
    }
    MapTile targetTile =
        GetMapTile(&gameContext->levelData, targetRow, targetColumn);
    if (targetTile == TILE_WALL || targetTile == TILE_GHOST_DOOR) {
      continue;
    }
    position->row = targetRow;
    position->column = targetColumn;
    if (ECS_HasComponent(activeEntity, COMPONENT_PLAYER_CONTROLLED)) {
      printf("[movement.c] - player Row = %d, player Column = %d\n",
             position->row, position->column);
    }
  }
}
