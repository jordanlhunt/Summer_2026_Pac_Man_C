#include "../../include/systems/collisionSystem.h"
#include <stdio.h>
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
  Entity edible = FindEdibleAt(playerPosition->row, playerPosition->column);
  if (edible != ENTITY_NULL) {
    ConsumeEdibleEntity(gameContext, edible);
  }
  int activeEntitesCount = ECS_GetActiveEntitiesCount();
  for (int i = 0; i < activeEntitesCount; i++) {
    Entity activeEntity = ECS_GetActiveEntity(i);
    Position *ghostPosition = ECS_GetPosition(activeEntity);
    if (ghostPosition->row != playerPosition->row ||
        ghostPosition->column != playerPosition->column) {
      continue;
    }
    Ghost *ghost = ECS_GetGhost(activeEntity);
    // Player has collieded with a frightened ghost
    if (gameContext->isFrightenedGhostModeActive == true) {
      gameContext->currentScore += BASE_GHOST_SCORE;
      ECS_DestroyEntity(activeEntity);
      printf("[collision.c] - A frightened ghost has been eaten!\n");
    } else {
      // Player dies
      // TODO: Reduce the number of lives restart the game
      printf("[collision.c] - PAC-MAN has collided with a Ghost! Game Over!\n");
    }
  }
}
static Entity FindEdibleAt(int row, int column) {
  int activeCount = ECS_GetActiveEntitiesCount();
  Entity edibleEntity;
  for (int i = 0; i < activeCount; i++) {
    edibleEntity = ECS_GetActiveEntity(i);
    if (ECS_HasComponents(edibleEntity,
                          COMPONENT_POSITION | COMPONENT_EDIBLE) == true) {
      Position *ediblePosition = ECS_GetPosition(edibleEntity);
      if (ediblePosition->row == row && ediblePosition->column == column) {
        return edibleEntity;
      }
    }
  }
  return ENTITY_NULL;
}
// *Consume* is a PAC-MAN pun. I would usually use "handle"
static void ConsumeEdibleEntity(GameContext *gameContext, Entity edibleEntity) {
  Edible *justEatenEdible = ECS_GetEdible(edibleEntity);
  gameContext->currentScore += justEatenEdible->scoreValue;
  if (justEatenEdible->typeEaten == POWER_PELLET ||
      justEatenEdible->typeEaten == DOT) {
    ReduceRemainingPellets(gameContext);
  }
  if (justEatenEdible->typeEaten == POWER_PELLET) {
    TriggerFrightenedMode(gameContext);
  }
  ECS_DestroyEntity(edibleEntity);
  if (gameContext->isRoundWon == false) {
    CheckForRoundWon(gameContext);
  }
}
