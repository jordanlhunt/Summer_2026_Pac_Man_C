#include "../../include/map.h"

#include <stdio.h>
#include <string.h>

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

void LoadMap(LevelData* levelData, const char* filePath) {
  FILE* mazeTextFile;
  const int lengthOfMazeLine = 28;
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
    // Create mapTiles
    if (row < MAP_HEIGHT) {
      for (int column = 0; column < MAP_WIDTH; column++) {
        if (currentLine[column] != '\0') {
          levelData->mapTiles[row][column] = CharToMapTile(currentLine[column]);
        } else {
          levelData->mapTiles[row][column] = TILE_EMPTY;
        }
      }
      row++;
    }
  }
  if (row < MAP_HEIGHT) {
    fprintf(stderr, "[map.c] - Warning: Expected %d rows, but found %d.\n",
            MAP_HEIGHT, row);
  }
  fclose(mazeTextFile);
}
void DrawMap(LevelData* levelData, SDL_Renderer* renderer) {}

enum MapTile GetMapTile(LevelData* levelData, int x, int y) {
  enum MapTile someMapTile = levelData->mapTiles[x][y];
  return someMapTile;
}