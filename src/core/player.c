#include "../../include/player.h"

#include <SDL2/SDL.h>

#include "../../include/entity.h"
#include "../../include/gamecontext.h"

// Initalize the player in the center of the screen for testing purposes the
// values for this will be changed in the future when I get the actual sprites.
void initializePlayer(GameContext* gameContext) {
  gameContext->player.x = 100.0f;
  gameContext->player.y = 100.0f;
  gameContext->player.velocity = 10;
  gameContext->player.width = 20;
  gameContext->player.height = 20;
}

// Update the player on GameContext->input
void updatePlayer(GameContext* gameContext) {
  if (gameContext->input.moveLeft) {
    gameContext->player.x = -gameContext->player.velocity;
  }
  if (gameContext->input.moveRight) {
    gameContext->player.x = gameContext->player.velocity;
  }
  if (gameContext->input.moveUp) {
    gameContext->player.y = -gameContext->player.velocity;
  }
  if (gameContext->input.moveDown) {
    gameContext->player.y = gameContext->player.velocity;
  }
}

void drawPlayer(SDL_Renderer* renderer, GameContext* gameContext) {
  SDL_Rect playerRect = {(int)gameContext->player.x, (int)gameContext->player.y,
                         gameContext->player.width, gameContext->player.height};
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // YELLOW for now
  SDL_RenderFillRect(renderer, &playerRect);
}