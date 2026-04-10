#include "include/main.h"
#include "include/common.h"
#include <SDL2/SDL_video.h>

int main(int argc, char *argv[]) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("[main.c] - SDL could not initialize! SDL_Error: %s\n",
           SDL_GetError());
    return 1;
  }
  SDL_Window *window = SDL_CreateWindow("Hac-Man", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_HIDDEN);
  SDL_Renderer *render =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(render, 100, 216, 107, 255); // Matrix Green
  SDL_RenderClear(render);
  SDL_RenderPresent(render);

  bool isQuit = false;
  SDL_Event sdl_event;
  SDL_ShowWindow(window);
  while (isQuit == false) {
    Uint32 startTime = SDL_GetTicks();
    while (SDL_PollEvent(&sdl_event) != 0) {
      if (sdl_event.type == SDL_QUIT) {
        isQuit = true;
      }
    }
    delayFramerate(startTime);
  }
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

void delayFramerate(Uint32 startTime) {
  Uint32 elapsedTime = SDL_GetTicks() - startTime;
  if (elapsedTime < FRAMERATE_DELAY) {
    SDL_Delay(FRAMERATE_DELAY - elapsedTime);
  }
}