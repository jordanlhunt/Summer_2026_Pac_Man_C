#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "common.h"
#include "ecs/ecs.h"
#include "ecs/entity.h"
#include "maptile.h"
#include <SDL2/SDL_render.h>
#define SPRITE_SIZE 8
#define PACMAN_ANIMATION_FPS 12.0f
#define GHOST_FLASHING_SPEED 6.0f
typedef struct SpriteSheet {
  SDL_Texture *texture;
  SDL_Rect wall;
  SDL_Rect dot;
  SDL_Rect powerPellet;
  SDL_Rect ghostDoor;
  SDL_Rect fruit;
  // PAC-MAN
  SDL_Rect pacmanRight;
  SDL_Rect pacmanLeft;
  SDL_Rect pacmanUp;
  SDL_Rect pacmanDown;
  // Ghosts
  SDL_Rect ghostNormal[4];
  SDL_Rect ghostFrightened;
  SDL_Rect ghostFlashing;
  SDL_Rect ghostEyes;
} SpriteSheet;
extern TTF_Font *globalFont;
extern SpriteSheet *globalSpriteSheet;
bool InitializeGraphics(SDL_Renderer *renderer, const char *spriteSheetPath);
bool InitializeTTF();
void ShutdownGraphics();
void ShutdownTTF();
void GraphicsDrawTile(SDL_Renderer *renderer, MapTile tile, float deltaTime);
void GraphicsDrawGhost(SDL_Renderer *renderer, Entity ghost, float deltaTime);
void GraphicsDrawPlayer(SDL_Renderer *renderer, Entity player, float deltaTime);
#endif
