#include "../../include/gamecontext.h"
#include "maptile.h"
#include <wchar.h>
void TriggerFrightenedMode(GameContext *gameContext) {
  if (gameContext == NULL) {
    return;
  }
  gameContext->isFrightenedGhostModeActive = true;
  gameContext->frightenedGhostModeTimer = FRIGHTEN_GHOST_MODE_DURATION;
}
void TriggerRoundWon(GameContext *gameContext) {
  if (gameContext == NULL) {
    return;
  }
  gameContext->isRoundWon = true;
}
void ReduceRemainingPellets(GameContext *gameContext) {
  if (gameContext == NULL) {
    return;
  }
  gameContext->remainingPellets -= 1;
  printf("Remaining Dots: %d\n", gameContext->remainingPellets);
}
void CheckForRoundWon(GameContext *gameContext) {
  if (gameContext->remainingPellets == 0) {
    TriggerRoundWon(gameContext);
    printf("Round Won! Great job player!\n");
  }
}
void InitializeGameContext(GameContext *gameContext) {
  gameContext->remainingPellets = NUMBER_OF_DOTS;
}
void HandlePlayerTileCollision(GameContext *gameContext, int row, int column,
                               MapTile collisionTile) {
  // NULL-Check
  if (gameContext == NULL) {
    return;
  }
  switch (collisionTile) {
  case TILE_DOT:
    gameContext->currentScore += DOT_PELLET_SCORE_VALUE;
    ReduceRemainingPellets(gameContext);
    SetMapTile(&gameContext->levelData, row, column, TILE_EMPTY);
    break;
  case TILE_POWER_PELLET:
    gameContext->currentScore += POWER_PELLET_SCORE_VALUE;
    ReduceRemainingPellets(gameContext);
    SetMapTile(&gameContext->levelData, row, column, TILE_EMPTY);
    TriggerFrightenedMode(gameContext);
    break;
  default:
    break;
  }
  if (gameContext->isRoundWon == false) {
    CheckForRoundWon(gameContext);
  }
}
// When the player collides with a  DOT, send a signal to the the gameContext to
// delete the dot update the score
void CollideWithDot(GameContext *gameContext, int row, int column,
                    MapTile collisionTile) {
  if (collisionTile == TILE_DOT) {
    collisionTile = TILE_EMPTY;
    gameContext->currentScore += DOT_PELLET_SCORE_VALUE;
    ReduceRemainingPellets(gameContext);
  }
  SetMapTile(&gameContext->levelData, row, column, collisionTile);
}
// When the player collides with a POWER_PELLET, send a signal to the
// gameContext to delete the dot, update the score, and set ghosts to
// "frightened"
void CollideWithPowerPellet(GameContext *gameContext, int row, int column,
                            MapTile collisionTile) {
  if (collisionTile == TILE_POWER_PELLET) {
    printf("CollideWithPowerPellet() is being called");
    collisionTile = TILE_EMPTY;
    gameContext->currentScore += POWER_PELLET_SCORE_VALUE;
    ReduceRemainingPellets(gameContext);
  }
  SetMapTile(&gameContext->levelData, row, column, collisionTile);
  TriggerFrightenedMode(gameContext);
}