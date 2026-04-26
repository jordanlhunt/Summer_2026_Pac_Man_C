#include "../../include/player.h"
#include "../../include/gamecontext.h"
#include "../../include/leveldata.h"
#include "../../include/map.h"

// Helper functions

// Before player can move to a location on the map see if it's valid
static bool CanPlayerMoveToLocation(LevelData *levelData, int mapColumn,
                                    int mapRow) {
  bool isMovementValid = true;
  // Bounds check
  if (mapRow < 0 || mapRow >= MAP_ROWS || mapColumn < 0 ||
      mapColumn >= MAP_COLUMNS) {
    return false;
  }
  enum MapTile targetMapTile = GetMapTile(levelData, mapRow, mapColumn);
  // Check if the targetMapTile a place where the player can be
  if (targetMapTile == TILE_WALL || targetMapTile == TILE_GHOST_DOOR) {
    return false;
  }
  return isMovementValid;
}

// Initialize the player to their spawn location as determined from the maze.txt
void InitializePlayer(GameContext *gameContext) {
  for (int row = 0; row < MAP_ROWS; row++) {
    for (int column = 0; column < MAP_COLUMNS; column++) {
      if (GetMapTile(&gameContext->levelData, row, column) == TILE_PLAYER) {
        gameContext->player.row = row;
        gameContext->player.column = column;
        gameContext->player.velocity = 1;
        gameContext->levelData.mapTiles[row][column] = TILE_EMPTY;
        return;
      }
    }
  }
}
// Update the player location on GameContext->input
void UpdatePlayer(GameContext *gameContext) {
  int newRow = gameContext->player.row;
  int newColumn = gameContext->player.column;
  if (gameContext->input.moveRight) {
    newColumn += gameContext->player.velocity;
  }
  if (gameContext->input.moveLeft) {
    newColumn -= gameContext->player.velocity;
  }
  if (gameContext->input.moveUp) {
    newRow -= gameContext->player.velocity;
  }
  if (gameContext->input.moveDown) {
    newRow += gameContext->player.velocity;
  }
  // Collision Check
  if (CanPlayerMoveToLocation(&gameContext->levelData, newColumn, newRow)) {
    gameContext->player.row = newRow;
    gameContext->player.column = newColumn;
  }
}
void DrawPlayer(GameContext *gameContext, SDL_Renderer *renderer) {
  int currentX = gameContext->player.column * MAP_GRID_CELL_SIZE;
  int currentY = gameContext->player.row * MAP_GRID_CELL_SIZE;
  SDL_Rect playerRect = {currentX, currentY, MAP_GRID_CELL_SIZE,
                         MAP_GRID_CELL_SIZE};
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // YELLOW for now
  SDL_RenderFillRect(renderer, &playerRect);
}
