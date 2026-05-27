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
  case UP:
    return DOWN;
  case DOWN:
    return UP;
  case LEFT:
    return RIGHT;
  case RIGHT:
    return LEFT;
  default:
    return ZERO_DIRECTION;
  }
}
static void MoveGhostTowardTarget(Entity ghostEntity, int targetRow,
                                  int targetColumn, LevelData *levelData) {
  Position *position = ECS_GetPosition(ghostEntity);
  Velocity *velocity = ECS_GetVelocity(ghostEntity);
  Ghost *ghost = ECS_GetGhost(ghostEntity);
  // Testing Purposes
  if (ghost->ghostType != GHOSTTYPE_BLINKY) {
    return;
  }
  Direction directions[4] = {UP, DOWN, LEFT, RIGHT};
  Direction directionToTarget = ZERO_DIRECTION;
  int bestDistanceToTarget = INT_MAX;
  for (int i = 0; i < (sizeof(directions) / sizeof(directions[0])); i++) {
    Direction candidateDirection = directions[i];
    // No backwards movement is allowed for ghosts
    if (candidateDirection == OppositeDirection(ghost->currentDirection)) {
      continue;
    }
    int newRow = position->row + DirectionToDeltaRow(candidateDirection);
    int newColumn =
        position->column + DirectionToDeltaColumn(candidateDirection);
    // Can't move through walls
    MapTile tileAheadOfGhost = GetMapTile(levelData, newRow, newColumn);
    if (tileAheadOfGhost == TILE_WALL) {
      continue;
    }
    if (tileAheadOfGhost == TILE_GHOST_DOOR) {
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
    velocity->deltaRow = DirectionToDeltaRow(directionToTarget);
    velocity->deltaColumn = DirectionToDeltaColumn(directionToTarget);
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
  switch (ghost->ghostType) {
  // Blinky directly targets the player's current location
  case GHOSTTYPE_BLINKY: {
    *targetRow = playerPosition->row;
    *targetColumn = playerPosition->column;
    break;
  }
  // Pink attempts to get "ahead" of the player to ambush them by going to
  // wherever 4 tiles ahead are. "machibuse" (待ち伏せ) is to ambush
  case GHOSTTYPE_PINKY: {
    *targetRow = playerPosition->row +
                 (DirectionToDeltaRow(playerControlled->currentDirection) * 4);
    *targetColumn =
        playerPosition->column +
        (DirectionToDeltaColumn(playerControlled->currentDirection) * 4);
    break;
  }
  default: {
    // TODO: Add logic for Inky and Clyde, will default to BLINKY for now.
    *targetRow = playerPosition->row;
    *targetColumn = playerPosition->column;
    break;
  }
  }
}

static void MoveGhostRandomly(Entity ghostEntity, LevelData *levelData) {
  Position *ghostPosition = ECS_GetPosition(ghostEntity);
  Velocity *ghostVelocity = ECS_GetVelocity(ghostEntity);
  Ghost *ghost = ECS_GetGhost(ghostEntity);
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
    MapTile mapTile = GetMapTile(levelData, newRow, newColumn);
    if (mapTile == TILE_WALL || mapTile == TILE_GHOST_DOOR) {
      continue;
    }
    validDirectionCount += 1;
    validDirections[validDirectionCount] = possibleDirection;
  }
  if (validDirectionCount > 0) {
    Direction chosenDirection = validDirections[rand() % validDirectionCount];
    ghost->currentDirection = chosenDirection;
    ghostVelocity->deltaRow = DirectionToDeltaRow(chosenDirection);
    ghostVelocity->deltaColumn = DirectionToDeltaColumn(chosenDirection);
  }
}

void GhostSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  int activeEntitiesCount = ECS_GetActiveEntitiesCount();
  for (int i = 0; i < activeEntitiesCount; i++) {
    Entity activeEntity = ECS_GetActiveEntity(i);
    if (ECS_HasComponents(activeEntity, COMPONENT_GHOST | COMPONENT_POSITION |
                                            COMPONENT_VELOCITY) == false) {
      continue;
    }
    Ghost *ghost = ECS_GetGhost(activeEntity);
    // Frigtened Mode
    if (gameContext->isFrightenedGhostModeActive == true) {
      MoveGhostRandomly(activeEntity, &gameContext->levelData);
    }
    // Scatter Mode
    else if (gameContext->currentGhostMode == GHOSTMODE_SCATTER) {
      MoveGhostTowardTarget(activeEntity, ghost->scatterTargetRow,
                            ghost->scatterTargetColumn,
                            &gameContext->levelData);
    }
    // Chase Mode
    else {
      int targetRow;
      int targetColumn;
      GetChaseTarget(activeEntity, gameContext, &targetRow, &targetRow);
      MoveGhostTowardTarget(activeEntity, targetRow, targetColumn,
                            &gameContext->levelData);
    }
    // TODO: ADD CHASE, FRIGHTENED, and EATEN
  }
}
