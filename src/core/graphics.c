#include "../../include/graphics.h"

SpriteSheet globalSpriteSheet;
TTF_Font globalFont = NULL;

static float staticPacmanAnimationTimer = 0.0f;
static int staticPacmanCurrentFrame;

bool InitializeGraphics(SDL_Renderer *renderer, const char *spriteSheetPath) {
  SDL_Surface *sourceSpriteSheetSurface = IMG_Load(spriteSheetPath);
  if (sourceSpriteSheetSurface == NULL) {
    printf("[graphics.c] - Failed to load sprite sheet: %s\n", IMG_GetError());
    return false;
  }
  // Load the source sheet with all the textures
  globalSpriteSheet->texture =
      SDL_CreateTextureFromSurface(renderer, sourceSpriteSheetSurface);
  SDL_FreeSurface(sourceSpriteSheetSurface);
  if (globalSpriteSheet == NULL) {
    printf("[graphics.c] - Failed to create globalSpriteSheet textue: %s",
           SDL_GetError());
    return false;
  }
}
