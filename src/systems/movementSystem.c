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
    float distanceToMoveEntity =
        velocity->tilesPerSecond * gameContext->deltaTime;
    // Advance sub-tile offsets
    position->offsetX += velocity->deltaColumn * distanceToMoveEntity;
    position->offsetY += velocity->deltaRow * distanceToMoveEntity;

    // Check if entity cross threshold into next column
    if (position->offsetX >= 1.0f) {
      int nextColumn = position->column + 1;
      if (nextColumn < MAP_COLUMNS) {
        MapTile nextTile =
            GetMapTile(&gameContext->levelData, position->row, nextColumn);
      }
    }

    if (ECS_HasComponent(activeEntity, COMPONENT_PLAYER_CONTROLLED)) {
      printf("[movement.c] - player Row = %d, player Column = %d\n",
             position->row, position->column);
    }
  }
}
