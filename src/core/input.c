#include "../../include/input.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../../include/gamecontext.h"

void handleEvent(SDL_Event* sdlEvent, GameContext* gameContext) {
  // Only process keyboard events
  if (sdlEvent->type != SDL_KEYDOWN && sdlEvent->type != SDL_KEYUP) {
    return;
  }

  bool isPressed = (sdlEvent->type == SDL_KEYDOWN);

  switch (sdlEvent->key.keysym.sym) {
    case SDLK_UP:
      gameContext->input.moveUp = isPressed;
      break;
    case SDLK_DOWN:
      gameContext->input.moveDown = isPressed;
      break;
    case SDLK_LEFT:
      gameContext->input.moveLeft = isPressed;
      break;
    case SDLK_RIGHT:
      gameContext->input.moveRight = isPressed;
      break;
    case SDLK_ESCAPE:
      // Only set quit on keydown, not keyup
      if (isPressed) gameContext->input.quitGame = true;
      break;
    case SDLK_p:
      // Toggle pause on keydown only
      if (isPressed)
        gameContext->input.pauseGame = !gameContext->input.pauseGame;
      break;
    default:
      break;
  }
}
