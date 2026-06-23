#include "../../include/systems/ghostSystem.h"
static int DistanceSquared(int row1, int column1, int row2, int column2) {
  int distanceSquared = 0;
  int deltaRow = row2 - row1;
  int deltaColumn = column2 - column1;
  distanceSquared = (deltaRow * deltaRow) + (deltaColumn * deltaColumn);
  return distanceSquared;
}
static int DirectionToDeltaRow(Direction direction) {
  if (direction == UP) {
    return -1;
  } else if (direction == DOWN) {
    return 1;
  } else {
    return 0;
  }
}
static int DirectionToDeltaColumn(Direction direction) {
  if (direction == LEFT) {
    return -1;
  } else if (direction == RIGHT) {
    return 1;
  } else {
    return 0;
  }
}
static Direction OppositeDirection(Direction direction) {
  switch (direction) {
  case UP: {
    return DOWN;
  }
  case DOWN: {
    return UP;
  }
  case LEFT: {
    return RIGHT;
  }
  case RIGHT: {
    return LEFT;
  }
  default: {
    return ZERO_DIRECTION;
  }
  }
}
// Every scatter/chase/frigtened transition requires an immediate reverse of
// direction
static void ReverseGhostDirection(Entity entity) {
  Velocity *ghostVelocity = ECS_GetVelocity(entity);
  Ghost *ghostEntity = ECS_GetGhost(entity);
  ghostVelocity->deltaRow *= -1;
  ghostVelocity->deltaColumn *= -1;
  ghostEntity->currentDirection =
      OppositeDirection(ghostEntity->currentDirection);
}
static void MoveGhostRandomly(Entity ghostEntity, LevelData *levelData) {
  Position *ghostPosition = ECS_GetPosition(ghostEntity);
  Velocity *ghostVelocity = ECS_GetVelocity(ghostEntity);
  Ghost *ghost = ECS_GetGhost(ghostEntity);
  // Only change direction when centered on a tile to fix the jitter. It was
  // changing direction every frame
  if (IsGhostCentered(ghostPosition) == false) {
    return;
  }
  Direction directions[4] = {UP, DOWN, LEFT, RIGHT};
  Direction validDirections[4];
  int validDirectionCount = 0;
  for (int i = 0; i < 4; i++) {
    Direction possibleDirection = directions[i];
    if (possibleDirection == OppositeDirection(ghost->currentDirection)) {
      continue;
    }
    int newRow = ghostPosition->row + DirectionToDeltaRow(possibleDirection);
    int newColumn =
        ghostPosition->column + DirectionToDeltaColumn(possibleDirection);
    // Bounds Check for edge cases, don't go off the map
    if (newRow < 0 || newRow >= MAP_ROWS || newColumn < 0 ||
        newColumn >= MAP_COLUMNS) {
      continue;
    }
    MapTile mapTile = GetMapTile(levelData, newRow, newColumn);
    if (mapTile == TILE_WALL || mapTile == TILE_GHOST_DOOR) {
      continue;
    }
    validDirections[validDirectionCount] = possibleDirection;
    validDirectionCount += 1;
  }
  if (validDirectionCount > 0) {
    Direction chosenDirection = validDirections[rand() % validDirectionCount];
    ghost->currentDirection = chosenDirection;
    ghostVelocity->deltaRow = DirectionToDeltaRow(chosenDirection);
    ghostVelocity->deltaColumn = DirectionToDeltaColumn(chosenDirection);
    ghostPosition->offsetX = 0.0f;
    ghostPosition->offsetY = 0.0f;
  }
}
static void MoveGhostTowardTarget(Entity ghostEntity, int targetRow,
                                  int targetColumn, LevelData *levelData,
                                  bool canPassThroughGhostDoor) {
  Position *ghostPosition = ECS_GetPosition(ghostEntity);
  Velocity *ghostVelocity = ECS_GetVelocity(ghostEntity);
  Ghost *ghost = ECS_GetGhost(ghostEntity);
  // Only change direction when centered on a tile to fix the jitter. It was
  // changing direction every frame
  if (IsGhostCentered(ghostPosition) == false) {
    return;
  }
  Direction directions[4] = {UP, DOWN, LEFT, RIGHT};
  Direction directionToTarget = ZERO_DIRECTION;
  int bestDistanceToTarget = INT_MAX;
  for (size_t i = 0; i < (sizeof(directions) / sizeof(directions[0])); i++) {
    Direction candidateDirection = directions[i];
    // No backwards movement is allowed for ghosts
    if (candidateDirection == OppositeDirection(ghost->currentDirection)) {
      continue;
    }
    int newRow = ghostPosition->row + DirectionToDeltaRow(candidateDirection);
    int newColumn =
        ghostPosition->column + DirectionToDeltaColumn(candidateDirection);
    // Bounds Check for edge cases, don't go off the map
    if (newRow < 0 || newRow >= MAP_ROWS || newColumn < 0 ||
        newColumn >= MAP_COLUMNS) {
      continue;
    }
    // Can't move through walls
    MapTile tileAheadOfGhost = GetMapTile(levelData, newRow, newColumn);
    if (tileAheadOfGhost == TILE_WALL) {
      continue;
    }
    if (tileAheadOfGhost == TILE_GHOST_DOOR &&
        canPassThroughGhostDoor == false) {
      continue;
    }
    int distanceSquared =
        DistanceSquared(targetRow, targetColumn, newRow, newColumn);
    if (distanceSquared < bestDistanceToTarget) {
      bestDistanceToTarget = distanceSquared;
      directionToTarget = candidateDirection;
    }
  }
  if (directionToTarget != ZERO_DIRECTION) {
    ghost->currentDirection = directionToTarget;
    ghostVelocity->deltaRow = DirectionToDeltaRow(directionToTarget);
    ghostVelocity->deltaColumn = DirectionToDeltaColumn(directionToTarget);
    // Snap Ghost to center on a turn
    ghostPosition->offsetX = 0.0f;
    ghostPosition->offsetY = 0.0f;
  }
}
// After being eaten, turn into eyes and return from current position back into
// the ghost house
static void UpdateGhostEyes(Entity ghostEntity, GameContext *gameContext) {
  Position *ghostPosition = ECS_GetPosition(ghostEntity);
  Ghost *ghost = ECS_GetGhost(ghostEntity);
  Velocity *ghostVelocity = ECS_GetVelocity(ghostEntity);
  ghostVelocity->tilesPerSecond = GHOST_SPEED_EYES;
  // Move to the Entrance
  if (ghostPosition->row != GHOST_HOUSE_ENTRANCE_ROW ||
      ghostPosition->column != GHOST_HOUSE_CENTER_COLUMN) {
    MoveGhostTowardTarget(ghostEntity, GHOST_HOUSE_ENTRANCE_ROW,
                          GHOST_HOUSE_ENTRANCE_COLUMN, &gameContext->levelData,
                          true);
    return;
  }
  // At entrance then pass through the ghost door
  MoveGhostTowardTarget(ghostEntity, GHOST_HOUSE_CENTER_ROW,
                        GHOST_HOUSE_CENTER_COLUMN, &gameContext->levelData,
                        true);
  // Enter the ghost house and reset the ghost to scatter to get back at it.
  if (ghostPosition->row == GHOST_HOUSE_CENTER_ROW &&
      ghostPosition->column == GHOST_HOUSE_CENTER_COLUMN) {
    ghost->ghostMode = GHOSTMODE_IN_GHOSTHOUSE;
    ghostVelocity->tilesPerSecond = GHOST_SPEED;
    ghostPosition->offsetX = 0.0f;
    ghostPosition->offsetY = 0.0f;
    printf("[ghostSystem.c] - Ghost has respawned.\n");
  }
}
static void UpdateGhostHouseExit(Entity ghostEntity, GameContext *gameContext) {
  Position *ghostPosition = ECS_GetPosition(ghostEntity);
  Ghost *ghost = ECS_GetGhost(ghostEntity);
  Velocity *ghostVelocity = ECS_GetVelocity(ghostEntity);
  int dotsEaten = NUMBER_OF_DOTS - gameContext->remainingPellets;
  // Ghosts exit the Ghost House after a threshold is met
  if (dotsEaten < ghost->exitGhostHouseThreshold) {
    ghostVelocity->deltaRow = 0;
    ghostVelocity->deltaColumn = 0;
    return;
  }
  if (ghost->ghostMode == GHOSTMODE_IN_GHOSTHOUSE) {
    ghost->ghostMode = GHOSTMODE_EXIT_GHOSTHOUSE;
  }
  // Leaving ghost needs to be be able to pass through the door
  MoveGhostTowardTarget(ghostEntity, GHOST_HOUSE_ENTRANCE_ROW,
                        GHOST_HOUSE_ENTRANCE_COLUMN, &gameContext->levelData,
                        true);
  if (ghostPosition->row == GHOST_HOUSE_ENTRANCE_ROW &&
      ghostPosition->column == GHOST_HOUSE_ENTRANCE_COLUMN) {
    ghost->ghostMode = GHOSTMODE_SCATTER;
    printf("[ghostSystem.c] - Ghost exited house.\n");
  }
}
// After leaving Scatter, the ghost needs to enter a chase mode. The dossier
// describes each ghosts behavior Right now I'm just focusing on blinky cause
// he's the easier. This ghost targets the player directly
static void GetChaseTarget(Entity entity, GameContext *gameContext,
                           int *targetRow, int *targetColumn) {
  Ghost *ghost = ECS_GetGhost(entity);
  Position *playerPosition = ECS_GetPosition(gameContext->playerEntity);
  PlayerControlled *playerControlled =
      ECS_GetPlayerControlled(gameContext->playerEntity);
  // Inky's target is a vector projection from Blinky's position through a point
  // 2 tiles ahead of PAC-MAN then doubled - the logic is found in The Dossier
  // [https://pacman.holenet.info/#CH4_Inky]
  Position *blinkyPosition = NULL;
  int activeCount = ECS_GetActiveEntitiesCount();
  for (int i = 0; i < activeCount; i++) {
    Entity activeEntity = ECS_GetActiveEntity(i);
    if (ECS_HasComponent(activeEntity, COMPONENT_GHOST)) {
      Ghost *ghostEntity = ECS_GetGhost(activeEntity);
      if (ghostEntity->ghostType == GHOSTTYPE_BLINKY) {
        blinkyPosition = ECS_GetPosition(activeEntity);
        break;
      }
    }
  }
  switch (ghost->ghostType) {
  // Blinky directly targets the player's current location
  // "oikake" (追い掛け) is to purse
  case GHOSTTYPE_BLINKY: {
    *targetRow = playerPosition->row;
    *targetColumn = playerPosition->column;
    break;
  }
  // Pink attempts to get "ahead" of the player to ambush them by going to
  // wherever 4 tiles ahead are.
  // "machibuse" (待ち伏せ) is to ambush
  case GHOSTTYPE_PINKY: {
    *targetRow = playerPosition->row +
                 (DirectionToDeltaRow(playerControlled->currentDirection) * 4);
    *targetColumn =
        playerPosition->column +
        (DirectionToDeltaColumn(playerControlled->currentDirection) * 4);
    break;
  }
    // Inky is the most complex tracking. Least predictable most erratic
    // "kimagure" (気まぐれ) means to be "fickle" or "capricious"
  case GHOSTTYPE_INKY: {
    // Setup the pivot point two tiles ahead of the player
    int pivotPointRow =
        playerPosition->row +
        (DirectionToDeltaRow(playerControlled->currentDirection) * 2);
    int pivotPointColumn =
        playerPosition->column +
        (DirectionToDeltaColumn(playerControlled->currentDirection) * 2);
    // Double the vector from Blinky to pivot
    if (blinkyPosition != NULL) {
      *targetRow = pivotPointRow + (pivotPointRow - blinkyPosition->row);
      *targetColumn =
          pivotPointColumn + (pivotPointColumn - blinkyPosition->column);
    } else {
      *targetRow = playerPosition->row;
      *targetColumn = playerPosition->column;
    }
    break;
  }
    // Clyde uses a proximity tracking
    // Chases directly when more than eight tiles way, but retreats to scatter
    // corner when with 8
    //  "otoboke" (お惚け) is to feign ignorance
  case GHOSTTYPE_CLYDE: {
    Position *clydePosition = ECS_GetPosition(entity);
    int distanceSquared =
        DistanceSquared(clydePosition->row, clydePosition->column,
                        playerPosition->row, playerPosition->column);
    if (distanceSquared > CLYDE_RETREAT_THRESHOLD) {
      // Chase Pac-Man
      *targetRow = playerPosition->row;
      *targetColumn = playerPosition->column;
    } else {
      // Retreat from Pac-Man
      Ghost *clydeGhost = ECS_GetGhost(entity);
      *targetRow = clydeGhost->scatterTargetRow;
      *targetColumn = clydeGhost->scatterTargetColumn;
    }
    break;
  }
  default: {
    *targetRow = playerPosition->row;
    *targetColumn = playerPosition->column;
    break;
  }
  }
}
void GhostSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  (void)renderer;
  int activeEntitiesCount = ECS_GetActiveEntitiesCount();
  for (int i = 0; i < activeEntitiesCount; i++) {
    Entity activeEntity = ECS_GetActiveEntity(i);
    if (ECS_HasComponents(activeEntity, COMPONENT_GHOST | COMPONENT_POSITION |
                                            COMPONENT_VELOCITY) == false) {
      continue;
    }
    Ghost *ghost = ECS_GetGhost(activeEntity);
    Velocity *ghostVelocity = ECS_GetVelocity(activeEntity);
    switch (ghost->ghostMode) {
    case GHOSTMODE_IN_GHOSTHOUSE:
    case GHOSTMODE_EXIT_GHOSTHOUSE: {
      UpdateGhostHouseExit(activeEntity, gameContext);
      break;
    }
    case GHOSTMODE_EATEN_EYES: {
      UpdateGhostEyes(activeEntity, gameContext);
      break;
    }
    case GHOSTMODE_FRIGHTENED: {
      if (gameContext->isFrightenedGhostModeActive == false) {
        ghost->ghostMode = GHOSTMODE_SCATTER;
        ghostVelocity->tilesPerSecond = GHOST_SPEED;
        ReverseGhostDirection(activeEntity);
        // Remove the edible component
        if (ECS_HasComponent(activeEntity, COMPONENT_EDIBLE) == true) {
          ECS_RemoveComponent(activeEntity, COMPONENT_EDIBLE);
        }
      } else {
        ghostVelocity->tilesPerSecond = GHOST_SPEED_FRIGHTENED;
        MoveGhostRandomly(activeEntity, &gameContext->levelData);
      }
      break;
    }
    case GHOSTMODE_CHASE:
    case GHOSTMODE_SCATTER: {
      if (gameContext->isFrightenedGhostModeActive == true) {
        ghost->ghostMode = GHOSTMODE_FRIGHTENED;
        // When Frightened it is now edible
        ECS_AddComponent(activeEntity, COMPONENT_EDIBLE);
        Edible *edibleGhost = ECS_GetEdible(activeEntity);
        edibleGhost->typeEaten = FRIGHTENED_GHOST;
        edibleGhost->scoreValue = BASE_GHOST_SCORE;
        ReverseGhostDirection(activeEntity);
        MoveGhostRandomly(activeEntity, &gameContext->levelData);
      } else if (gameContext->currentGhostMode == GHOSTMODE_SCATTER) {
        if (ghost->ghostMode != GHOSTMODE_SCATTER) {
          ReverseGhostDirection(activeEntity);
        }
        ghost->ghostMode = GHOSTMODE_SCATTER;
        MoveGhostTowardTarget(activeEntity, ghost->scatterTargetRow,
                              ghost->scatterTargetColumn,
                              &gameContext->levelData, false);
      } else {
        if (ghost->ghostMode != GHOSTMODE_CHASE) {
          ReverseGhostDirection(activeEntity);
        }
        ghost->ghostMode = GHOSTMODE_CHASE;
        int targetRow = 0;
        int targetColumn = 0;
        GetChaseTarget(activeEntity, gameContext, &targetRow, &targetColumn);
        MoveGhostTowardTarget(activeEntity, targetRow, targetColumn,
                              &gameContext->levelData, false);
      }
      break;
    }
    default: {
      break;
    }
    }
  }
}
