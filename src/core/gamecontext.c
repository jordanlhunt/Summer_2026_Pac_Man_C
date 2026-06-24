#include "../../include/gamecontext.h"

static void LoadHighScore(GameContext *gameContext) {
  FILE *saveFile = fopen(HIGH_SCORE_SAVE_FILE, "r");
  if (saveFile != NULL) {
    fread(&gameContext->highScore, sizeof(int), 1, saveFile);
    fclose(saveFile);
  } else {
    gameContext->highScore = 0;
  }
}

static void SaveHighScore(GameContext *gameContext) {
  FILE *saveFile = fopen(HIGH_SCORE_SAVE_FILE, "w");
  if (saveFile != NULL) {
    fwrite(&gameContext->highScore, sizeof(int), 1, saveFile);
    fclose(saveFile);
  }
}

static void ResetGameRound(GameContext *gameContext) {
  srand(0);
  ResetPlayerPosition(gameContext);
  gameContext->isFrightenedGhostModeActive = false;
  gameContext->frightenedGhostModeTimer = 0.0f;
  gameContext->currentGhostMode = GHOSTMODE_SCATTER;
  gameContext->ghostModeTimer = SCATTER_TIME_LIMIT;
}
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
  srand(0); // Frightened movement is deterministic per-level
  gameContext->remainingPellets = NUMBER_OF_DOTS;
  gameContext->currentScore = 0;
  gameContext->isFrightenedGhostModeActive = false;
  gameContext->isRoundWon = false;
  gameContext->currentGhostMode = GHOSTMODE_SCATTER;
  gameContext->ghostModeTimer = SCATTER_TIME_LIMIT;
  gameContext->deltaTime = 0.0f;
  gameContext->playerLives = 3;
  gameContext->pendingDirection = ZERO_DIRECTION;
  LoadHighScore(gameContext);
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
void TriggerGameOver(GameContext *gameContext) {
  if (gameContext == NULL) {
    return;
  }
  if (gameContext->isGameOver) {
    return;
  }
  if (gameContext->currentScore > gameContext->highScore) {
    gameContext->highScore = gameContext->currentScore;
    SaveHighScore(gameContext);
    printf("[gamecontext.c] - NEW HIGH SCORE!\n");
  }
  gameContext->isGameOver = true;
  printf("[gamecontext.c] - Game Over. Final Score: %d\n",
         gameContext->currentScore);
}
void TriggerPlayerDeath(GameContext *gameContext) {
  if (gameContext == NULL) {
    return;
  }
  if (gameContext->isGameOver == true) {
    return;
  }
  gameContext->playerLives -= 1;
  printf("[gamecontext.c] - Player has died. Lives remaining: %d\n",
         gameContext->playerLives);
  if (gameContext->playerLives <= 0) {
    TriggerGameOver(gameContext);
    return;
  }
  ResetGameRound(gameContext);
}
void ResetPlayerPosition(GameContext *gameContext) {
  if (gameContext == NULL) {
    return;
  }
  Position *position = ECS_GetPosition(gameContext->playerEntity);
  Velocity *velocity = ECS_GetVelocity(gameContext->playerEntity);
  position->row = gameContext->playerSpawnRow;
  position->column = gameContext->playerSpawnColumn;
  position->offsetX = 0.0f;
  position->offsetY = 0.0f;
  velocity->deltaRow = 0;
  velocity->deltaColumn = 0;
  gameContext->pendingDirection = ZERO_DIRECTION;
}
