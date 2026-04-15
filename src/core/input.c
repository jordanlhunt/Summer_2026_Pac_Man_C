#include "../../include/input.h"
#include "../../include/gamecontext.h"
#include <SDL2/SDL_keycode.h>
#include <stdbool.h>

void handleEvent(SDL_Event *sdlEvent, GameContext *gameContext) {
  handleInput(sdlEvent->key.keysym.sym, gameContext);
}

void handleInput(SDL_KeyCode keyCode, GameContext *gameContext) {
  switch (keyCode) {
  case SDLK_UP:
    gameContext->input.moveUp = true;
    break;
  case SDLK_DOWN:
    gameContext->input.moveDown = true;
    break;
  case SDLK_LEFT:
    gameContext->input.moveLeft = true;
    break;
  case SDLK_RIGHT:
    gameContext->input.moveRight = true;
    break;
  case SDLK_ESCAPE:
    gameContext->input.quitGame = true;
    break;
  case SDLK_p:
    gameContext->input.pauseGame = true;
    break;
  default:
    break;
  }
}