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
  if (gameContext->remainingPellets == 0) {
    TriggerRoundWon(gameContext);
    printf("Round Won! Great job player!\n");
  }
}
void InitializeGameContext(GameContext *gameContext) {
  gameContext->remainingPellets = NUMBER_OF_DOTS;
}
