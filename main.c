#include "include/common.h"

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("[main.c] - SDL could not initialize! SDL_Error: %s\n",
           SDL_GetError());
    return 1;
  }
  SDL_Window *window = SDL_CreateWindow("Hac-Man", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer *render =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  bool isQuit = false;
  SDL_Event sdl_event;
  while (isQuit == false) {
    while (SDL_PollEvent(&sdl_event) != 0) {
      if (sdl_event.type == SDL_QUIT) {
        isQuit = true;
      }

      SDL_SetRenderDrawColor(render, 100, 216, 107, 255); // Matrix Green
      SDL_RenderClear(render);
      SDL_RenderPresent(render);
    }
  }
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
