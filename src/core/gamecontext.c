#include "../../include/gamecontext.h"

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
}

void CheckForRoundWon(GameContext *gameContext) {
  if (gameContext->remainingPellets == 0) {
    TriggerRoundWon(gameContext);
  }
}