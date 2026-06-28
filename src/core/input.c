#include "../../include/input.h"
#include "../../include/gamecontext.h"
#include "../../include/gameinitialization.h"
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
  // Treat SPACE like the start button at the arcade
  case SDLK_SPACE: {
    if (isPressed == false) {
      break;
    }
    switch (gameContext->currentGameState) {
      // Start the game
    case GAMESTATE_TITLE: {
      ResetGameRound(gameContext);
      gameContext->currentGameState = GAMESTATE_PLAYING;
      break;
    }
    // Pause the game
    case GAMESTATE_PLAYING: {
      gameContext->currentGameState = GAMESTATE_PAUSED;
      break;
    }
    // Unpause the game
    case GAMESTATE_PAUSED: {
      gameContext->currentGameState = GAMESTATE_PLAYING;
      break;
    }
    // Restart the game, wipe everything start anew
    case GAMESTATE_GAME_OVER: {
      ECS_Initialize();
      InitializeSystems();
      InitializeGameContext(gameContext);
      LoadMap(&gameContext->levelData, PATH_TO_MAZE_FILE,
              gameContext->ghostsEntities);
      Entity player = ECS_CreateEntity();
      InitializePlayer(gameContext, player);
      gameContext->playerEntity = player;
      gameContext->currentGameState = GAMESTATE_TITLE;
      break;
    }
    default: {
      break;
    }
    }
  }
  }
}