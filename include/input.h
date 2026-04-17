#ifndef INPUT_H
#define INPUT_H
#include "common.h"
typedef struct {
  bool moveUp;
  bool moveDown;
  bool moveLeft;
  bool moveRight;
  bool quitGame;
  bool pauseGame;
} Input;
// Forward declaration to avoid circular includes
typedef struct GameContext GameContext;
void handleEvent(SDL_Event* sdlEvent, GameContext* gameContext);
#endif