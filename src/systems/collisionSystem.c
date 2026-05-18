#include "../../include/systems/collisionSystem.h"

void CollisionSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  Entity playerEntity = gameContext->playerEntity;

  if (ECS_HasComponent(playerEntity, COMPONENT_POSITION) == false) {
    return;
  }
  if (ECS_HasComponent(playerEntity, COMPONENT_VELOCITY) == false) {
    printf("[collisionSystem.c] - Object does not have velocity component");
    return;
  }
  Velocity *velocity = ECS_GetVelocity(gameContext->playerEntity);
  if (velocity->deltaRow == 0 && velocity->deltaColumn == 0) {
    return;
  }
  Position *playerPosition = ECS_GetPosition(gameContext->playerEntity);
  MapTile collisionTile = GetMapTile(
      &gameContext->levelData, playerPosition->row, playerPosition->column);
  HandlePlayerTileCollision(gameContext, playerPosition->row,
                            playerPosition->column);
}
