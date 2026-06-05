#include "../../include/systems/collisionSystem.h"
#include <stdio.h>
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
  if (justEatenEdible->typeEaten == FRIGHTENED_GHOST) {
    Ghost *ghost = ECS_GetGhost(edibleEntity);
    ghost->ghostMode = GHOSTMODE_EATEN_EYES;
    printf("[collision.c] - A frightened ghost has been eaten! Current "
           "Score: %d\n",
           gameContext->currentScore);
    // Don't destroy FRIGRENED_GHOSTS because they must remain on the map
    return;
  }
  // Destroy Dots, Power Pellets, and/or fruit
  ECS_DestroyEntity(edibleEntity);
  if (gameContext->isRoundWon == false) {
    CheckForRoundWon(gameContext);
  }
}

void CollisionSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  (void)renderer;
  Entity playerEntity = gameContext->playerEntity;
  if (ECS_HasComponent(playerEntity, COMPONENT_POSITION) == false) {
    return;
  }
  if (ECS_HasComponent(playerEntity, COMPONENT_VELOCITY) == false) {
    printf("[collisionSystem.c] - Object does not have velocity component");
    return;
  }
  Position *playerPosition = ECS_GetPosition(gameContext->playerEntity);
  Entity edible = FindEdibleAt(playerPosition->row, playerPosition->column);
  // Eat Frightened Ghosts, Dots, Power Pellets, and/or fruit
  if (edible != ENTITY_NULL) {
    ConsumeEdibleEntity(gameContext, edible);
  }

  // Player colliding with Ghosts
  int activeEntitesCount = ECS_GetActiveEntitiesCount();
  for (int i = 0; i < activeEntitesCount; i++) {
    Entity activeEntity = ECS_GetActiveEntity(i);
    // Skip over non-ghosts
    if (ECS_HasComponent(activeEntity, COMPONENT_GHOST) == false) {
      continue;
    }
    // Skip over the player
    if (activeEntity == playerEntity) {
      continue;
    }

    Ghost *ghost = ECS_GetGhost(activeEntity);
    Position *ghostPosition = ECS_GetPosition(activeEntity);

    if (ghostPosition->row != playerPosition->row ||
        ghostPosition->column != playerPosition->column) {
      continue;
    }
    // Kill the player if the player collides with a NOT frightened and NOT
    // EYE_MODE ghost
    if (ghost->ghostMode != GHOSTMODE_FRIGHTENED &&
        ghost->ghostMode != GHOSTMODE_EATEN_EYES) {
      // Player dies
      TriggerPlayerDeath(gameContext);
      return;
    }
  }
}
