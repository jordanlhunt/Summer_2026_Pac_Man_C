#include "../../include/map.h"
#include <SDL2/SDL_render.h>
// Helper Function
static enum MapTile CharToMapTile(char mapChar) {
  switch (mapChar) {
  case 'W':
    return TILE_WALL;
  case '.':
    return TILE_DOT;
  case '+':
    return TILE_POWER_PELLET;
  case ' ':
    return TILE_EMPTY;
  case 'X':
    return TILE_PLAYER;
  case 'B':
  case 'P':
  case 'I':
  case 'C':
    return TILE_GHOST;
  case '-':
    return TILE_GHOST_DOOR;
  case 'F':
    return TILE_FRUIT;
  default:
    return TILE_EMPTY;
  }
}
void LoadMap(LevelData *levelData, const char *filePath) {
  FILE *mazeTextFile;
  const int lengthOfMazeLine =
      30; // It's 30 because of the newline and null terminator
  int row = 0;
  // Open the maze.txt
  printf("[map.c] - Loading maze.txt\n");
  mazeTextFile = fopen(filePath, "rt");
  if (mazeTextFile == NULL) {
    perror("[map.c] - Unable to load maze.txt");
    exit(EXIT_FAILURE);
  }
  // Create array to hold current line
  char currentLine[lengthOfMazeLine];
  // Process the line - Skip comments and empty lines, once you get to the maze
  // trim the line and create mapTiles from the line holds
  while (fgets(currentLine, sizeof(currentLine), mazeTextFile)) {
    // Skip comments and empty lines
    if (currentLine[0] == ';' || currentLine[0] == '\n' ||
        currentLine[0] == '\0') {
      continue;
    }
    // Trim the line
    currentLine[strcspn(currentLine, "\r\n")] = '\0';
    // Loop through the .txt file and get populate the levelData->mapTiles
    if (row < MAP_ROWS) {
      for (int column = 0; column < MAP_COLUMNS; column++) {
        if (currentLine[column] != '\0') {
          levelData->mapTiles[row][column] = CharToMapTile(currentLine[column]);
        } else {
          levelData->mapTiles[row][column] = TILE_EMPTY;
        }
      }
      row++;
    }
  }
  // Error Handling
  if (row < MAP_ROWS) {
    fprintf(stderr, "[map.c] - Warning: Expected %d rows, but found %d.\n",
            MAP_ROWS, row);
  }
  fclose(mazeTextFile);
}
void DrawMap(LevelData *levelData, SDL_Renderer *renderer) {
  SDL_Rect tileRect;
  tileRect.w = MAP_GRID_CELL_SIZE;
  tileRect.h = MAP_GRID_CELL_SIZE;
  for (int row = 0; row < MAP_ROWS; row++) {
    for (int col = 0; col < MAP_COLUMNS; col++) {
      enum MapTile newMapTile = levelData->mapTiles[row][col];
      tileRect.x = col * MAP_GRID_CELL_SIZE;
      tileRect.y = row * MAP_GRID_CELL_SIZE;
      switch (newMapTile) {
      case TILE_WALL:
        // Walls are Blue
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        break;
      case TILE_GHOST_DOOR:
        // Ghost Door is Pink
        // TODO: Look at official Pac-Man game and make it whatever the game
        // actually is
        SDL_SetRenderDrawColor(renderer, 255, 105, 108, 255);
        break;
      case TILE_DOT:
        // Dots are peach for now
        // TODO: Look at official Pac-Man game and make it whatever the game
        // actually is
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        break;
      case TILE_POWER_PELLET:
        // Power Pallets are white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        break;
      case TILE_PLAYER:
        // Player is Yellow
        // TODO: Make the player actually a player entity rather than just a
        // marker on the map
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        break;
      case TILE_GHOST:
        // Ghosts are RED for now.
        // TODO: Make each ghost it's own ghost entity rather than than just a
        // marker on the map and draw its specific ghost logic
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        break;
      case TILE_FRUIT:
        // Fruit is orange for now.
        // TODO: Make each fruit it's own fruit entity rather than just a marker
        // on the map.
        SDL_SetRenderDrawColor(renderer, 255, 154, 51, 255);
        break;
      case TILE_EMPTY:
        break;
      default:
        break;
      }
      SDL_RenderFillRect(renderer, &tileRect);
    }
  }
}
enum MapTile GetMapTile(LevelData *levelData, int x, int y) {
  enum MapTile someMapTile = levelData->mapTiles[x][y];
  return someMapTile;
}