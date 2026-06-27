#include "../../include/input.h"
#include "../../include/gamecontext.h"
void handleEvent(SDL_Event *sdlEvent, GameContext *gameContext) {
  // Only process keyboard events
  if (sdlEvent->type != SDL_KEYDOWN && sdlEvent->type != SDL_KEYUP) {
    return;
  }
  bool isPressed = (sdlEvent->type == SDL_KEYDOWN);
  switch (sdlEvent->key.keysym.sym) {
  case SDLK_UP: {
    gameContext->pendingDirection = UP;
    break;
  }
  case SDLK_DOWN: {
    gameContext->pendingDirection = DOWN;
    break;
  }
  case SDLK_LEFT: {
    gameContext->pendingDirection = LEFT;
    break;
  }
  case SDLK_RIGHT: {
    gameContext->pendingDirection = RIGHT;
    break;
  }
  case SDLK_ESCAPE: {
    // Only set quit on keydown, not keyup
    if (isPressed) {
      gameContext->input.quitGame = true;
    }
    break;
  }
  case SDLK_SPACE: {
    printf("[input.c] - Space was pressed\n");
    if (isPressed == true &&
        gameContext->currentGameState == GAMESTATE_PLAYING) {
      gameContext->currentGameState = GAMESTATE_PAUSED;
    } else if (isPressed == true &&
               gameContext->currentGameState == GAMESTATE_PAUSED) {
      gameContext->currentGameState = GAMESTATE_PLAYING;
    }
    break;
  }
  default: {
    break;
  }
  }
}
