#include "../include/main.h"
int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("[main.c] - SDL could not initialize! SDL_Error: %s\n",
           SDL_GetError());
    {
      return 1;
    }
  }
  SDL_Window *window = SDL_CreateWindow("Hac-Man", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_HIDDEN);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  GameContext gameContext = {0};
  LoadMap(&gameContext.levelData, PATH_TO_MAZE_FILE);
  InitializePlayer(&gameContext);
  bool isQuit = false;
  SDL_Event sdl_event;
  SDL_ShowWindow(window);
  while (isQuit == false) {
    Uint32 startTime = SDL_GetTicks();
    while (SDL_PollEvent(&sdl_event) != 0) {
      if (sdl_event.type == SDL_QUIT) {
        isQuit = true;
      }
      handleEvent(&sdl_event, &gameContext);
    }
    if (gameContext.input.quitGame == true) {
      isQuit = true;
    }
    UpdatePlayer(&gameContext);
    SDL_SetRenderDrawColor(renderer, 100, 216, 107, 255); // Matrix Green
    SDL_RenderClear(renderer);
    DrawMap(&gameContext.levelData, renderer);
    DrawPlayer(&gameContext, renderer);
    SDL_RenderPresent(renderer);
    delayFramerate(startTime);
  }
  cleanup(renderer, window);
  return 0;
}
/* Caps the game's execution speed to maintain a consistent 60 FPS */
void delayFramerate(Uint32 startTime) {
  Uint32 elapsedTime = SDL_GetTicks() - startTime;
  if (elapsedTime < FRAMERATE_DELAY) {
    SDL_Delay(FRAMERATE_DELAY - elapsedTime);
  }
}
/* Tears down the game on close */
void cleanup(SDL_Renderer *renderer, SDL_Window *sdlWindow) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(sdlWindow);
  SDL_Quit();
}