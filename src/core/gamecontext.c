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
  printf("Remaining Dots: %d\n", gameContext->remainingPellets);
}
void CheckForRoundWon(GameContext *gameContext) {
  if (gameContext == NULL) {
    return;
  }
  if (gameContext->remainingPellets == 0) {
    TriggerRoundWon(gameContext);
    printf("Round Won! Great job player!\n");
  }
}
void InitializeGameContext(GameContext *gameContext) {
  gameContext->remainingPellets = NUMBER_OF_DOTS;
  gameContext->currentScore = 0;
  gameContext->isFrightenedGhostModeActive = false;
  gameContext->isRoundWon = false;
  gameContext->currentGhostMode = GHOSTMODE_SCATTER;
  gameContext->ghostModeTimer = SCATTER_TIME_LIMIT;
}

void UpdateGhostTimer(GameContext *gameContext, float deltaTime) {
  if (gameContext == NULL) {
    return;
  }
  // Do not switch between Chase and Scatter when ghosts are frightened
  if (gameContext->isFrightenedGhostModeActive) {
    return;
  }
  gameContext->ghostModeTimer -= deltaTime;
  if (gameContext->ghostModeTimer <= 0.0f) {
    if (gameContext->currentGhostMode == GHOSTMODE_SCATTER) {
      gameContext->currentGhostMode = GHOSTMODE_CHASE;
      gameContext->ghostModeTimer = CHASE_TIME_LIMIT;
    } else {
      gameContext->currentGhostMode = GHOSTMODE_SCATTER;
      gameContext->ghostModeTimer = SCATTER_TIME_LIMIT;
    }
  }
}
