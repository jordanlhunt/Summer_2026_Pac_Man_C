#include "../../include/gameinitialization.h"

bool InitializeSDL(SDLContext *sdlContext) {
  if (SDL_Init(SDL_INIT_VIDEO < 0)) {
    printf("[gameInitialization.c] - SDL failed to initialize: %s\n",
           SDL_GetError());
  }
}