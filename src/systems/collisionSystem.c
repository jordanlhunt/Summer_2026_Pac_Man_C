#include "../../include/systems/collisionSystem.h"

void CollisionSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  if (ECS_HasComponent(gameContext->playerEntity, COMPONENT_POSITION) ==
      false) {
    return;
  }
  Velocity *velocity = ECS_GetVelocity(gameContext->playerEntity);
  if (ECS_HasComponent(gameContext->playerEntity, COMPONENT_VELOCITY) ==
      false) {
    printf("[collisionSystem.c] - Object does not have velocity component");
    return;
  }
  if (velocity->deltaRow == 0 && velocity->deltaColumn == 0) {
    return;
  }
  Position *position = ECS_GetPosition(gameContext->playerEntity);
  MapTile collisionTile =
      GetMapTile(&gameContext->levelData, position->row, position->column);
  HandlePlayerTileCollision(gameContext, position->row, position->column,
                            collisionTile);
}
