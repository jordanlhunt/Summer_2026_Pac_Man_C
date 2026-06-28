#include "../../include/map.h"
// Helper Function
static MapTile CharToMapTile(char mapChar) {
  switch (mapChar) {
  case 'W': {
    return TILE_WALL;
  }
  case '.': {
    return TILE_DOT;
  }
  case '+': {
    return TILE_POWER_PELLET;
  }
  case ' ': {
    return TILE_EMPTY;
  }
  case 'X': {
    return TILE_PLAYER;
  }
  case '-': {
    return TILE_GHOST_DOOR;
  }
  case 'F': {
    return TILE_FRUIT;
  }
  default: {
    return TILE_EMPTY;
  }
  }
}
static void SpawnGhost(Entity ghostEntities[], GhostType ghostType, int row,
                       int column) {
  struct SpawnGhostData {
    int red;
    int green;
    int blue;
    int scatterRow;
    int scatterColumn;
    int releaseThreshold;
    GhostMode ghostmode;
  } ghostSpawnData[GHOST_COUNT] = {
      // Designated initializers for accuracy and clarity, I like this method
      // [https://gcc.gnu.org/onlinedocs/gcc/Designated-Inits.html]
      [GHOSTTYPE_BLINKY] = {.red = 255,
                            .green = 0,
                            .blue = 0,
                            .scatterRow = 0,
                            .scatterColumn = MAP_COLUMNS - 1,
                            .releaseThreshold = 0,
                            .ghostmode = GHOSTMODE_SCATTER},
      [GHOSTTYPE_PINKY] = {.red = 255,
                           .green = 184,
                           .blue = 255,
                           .scatterRow = 0,
                           .scatterColumn = 0,
                           .releaseThreshold = RELEASE_THRESHOLD_PINKY,
                           .ghostmode = GHOSTMODE_IN_GHOSTHOUSE},
      [GHOSTTYPE_INKY] = {.red = 0,
                          .green = 255,
                          .blue = 255,
                          .scatterRow = MAP_ROWS - 1,
                          .scatterColumn = MAP_COLUMNS - 1,
                          .releaseThreshold = RELEASE_THRESHOLD_INKY,
                          .ghostmode = GHOSTMODE_IN_GHOSTHOUSE},
      [GHOSTTYPE_CLYDE] = {.red = 255,
                           .green = 184,
                           .blue = 82,
                           .scatterRow = MAP_ROWS - 1,
                           .scatterColumn = 0,
                           .releaseThreshold = RELEASE_THRESHOLD_CLYDE,
                           .ghostmode = GHOSTMODE_IN_GHOSTHOUSE}};
  Entity newEntity = ECS_CreateEntity();
  ghostEntities[ghostType] = newEntity;
  ECS_AddComponent(newEntity, COMPONENT_POSITION | COMPONENT_VELOCITY |
                                  COMPONENT_RENDERABLE | COMPONENT_GHOST);
  Ghost *ghost = ECS_GetGhost(newEntity);
  ghost->ghostType = ghostType;
  ghost->ghostMode = ghostSpawnData[ghostType].ghostmode;
  ghost->currentDirection = ZERO_DIRECTION;
  ghost->scatterTargetColumn = ghostSpawnData[ghostType].scatterColumn;
  ghost->scatterTargetRow = ghostSpawnData[ghostType].scatterRow;
  ghost->exitGhostHouseThreshold = ghostSpawnData[ghostType].releaseThreshold;
  Velocity *ghostVelocity = ECS_GetVelocity(newEntity);
  ghostVelocity->deltaRow = 0;
  ghostVelocity->deltaColumn = 0;
  ghostVelocity->tilesPerSecond = GHOST_SPEED;
  Position *ghostPosition = ECS_GetPosition(newEntity);
  ghostPosition->row = row;
  ghostPosition->column = column;
  Renderable *renderData = ECS_GetRenderable(newEntity);
  renderData->red = ghostSpawnData[ghostType].red;
  renderData->green = ghostSpawnData[ghostType].green;
  renderData->blue = ghostSpawnData[ghostType].blue;
  renderData->alpha = 255;
  renderData->width = MAP_GRID_CELL_SIZE;
  renderData->height = MAP_GRID_CELL_SIZE;
  renderData->renderLayer = RENDERLAYER_GHOST;
  printf("[map.c] - Ghost %d spawned at row=%d and column=%d\n", ghostType, row,
         column);
}
void LoadMap(LevelData *levelData, const char *filePath,
             Entity ghostEntities[]) {
  FILE *mazeTextFile;
  const int LENGTH_OF_MAZE_LINE = MAP_COLUMNS + 2;
  int row = 0;
  // Create array to hold current line
  char currentLine[LENGTH_OF_MAZE_LINE];
  // Open the maze.txt
  printf("[map.c] - Loading maze.txt\n");
  mazeTextFile = fopen(filePath, "rt");
  if (mazeTextFile == NULL) {
    perror("[map.c] - Unable to load maze.txt");
    exit(EXIT_FAILURE);
  }
  // Process the line - Skip comments and empty lines, once you get to the
  // maze trim the line and create mapTiles from the line holds
  while (fgets(currentLine, sizeof(currentLine), mazeTextFile)) {
    // Check if hit the end of the line with EOF or '\n'
    bool hasReadFullLine = (strchr(currentLine, '\n')) != NULL;
    // If the buffer for this line is too small 'drain' it
    // This is mostly for the comments in the maze.txt file
    if (!hasReadFullLine) {
      int endOfLineChar;
      while ((endOfLineChar = fgetc(mazeTextFile)) != '\n' &&
             endOfLineChar != EOF)
        // Discards the remain characters until it hits the '\n' or EOF
        ;
    }
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
        char currentCharacter = currentLine[column];
        if (currentCharacter == '\0') {
          continue;
        }
        if (currentCharacter == 'B' || currentCharacter == 'P' ||
            currentCharacter == 'I' || currentCharacter == 'C') {
          printf("[map.c] - Found ghost '%c' at row=%d col=%d\n",
                 currentCharacter, row, column);
          GhostType ghostType;
          if (currentCharacter == 'B') {
            ghostType = GHOSTTYPE_BLINKY;
          } else if (currentCharacter == 'P') {
            ghostType = GHOSTTYPE_PINKY;
          } else if (currentCharacter == 'I') {
            ghostType = GHOSTTYPE_INKY;
          } else {
            ghostType = GHOSTTYPE_CLYDE;
          }
          SpawnGhost(ghostEntities, ghostType, row, column);
          levelData->mapTiles[row][column] = TILE_EMPTY;
          continue;
        }
        // Create the MapTile
        MapTile mapTile = CharToMapTile(currentCharacter);
        switch (mapTile) {
        case TILE_DOT: {
          Entity dotEntity = ECS_CreateEntity();
          ECS_AddComponent(dotEntity, COMPONENT_POSITION | COMPONENT_EDIBLE |
                                          COMPONENT_RENDERABLE);
          Renderable *dotRenderData = ECS_GetRenderable(dotEntity);
          dotRenderData->red = 240;
          dotRenderData->blue = 240;
          dotRenderData->green = 240;
          dotRenderData->alpha = 255;
          dotRenderData->width = MAP_GRID_CELL_SIZE;
          dotRenderData->height = MAP_GRID_CELL_SIZE;
          dotRenderData->renderLayer = RENDERLAYER_EDIBLE;
          Position *dotPosition = ECS_GetPosition(dotEntity);
          dotPosition->row = row;
          dotPosition->column = column;
          Edible *dotEdible = ECS_GetEdible(dotEntity);
          dotEdible->scoreValue = DOT_PELLET_SCORE_VALUE;
          dotEdible->typeEaten = DOT;
          levelData->mapTiles[row][column] = TILE_EMPTY;
          break;
        }
        case TILE_POWER_PELLET: {
          Entity powerPelletEntity = ECS_CreateEntity();
          ECS_AddComponent(powerPelletEntity, COMPONENT_POSITION |
                                                  COMPONENT_EDIBLE |
                                                  COMPONENT_RENDERABLE);
          Renderable *powerPelletRenderData =
              ECS_GetRenderable(powerPelletEntity);
          powerPelletRenderData->red = 100;
          powerPelletRenderData->blue = 100;
          powerPelletRenderData->green = 100;
          powerPelletRenderData->alpha = 255;
          powerPelletRenderData->width = MAP_GRID_CELL_SIZE;
          powerPelletRenderData->height = MAP_GRID_CELL_SIZE;
          powerPelletRenderData->renderLayer = RENDERLAYER_EDIBLE;
          Position *powerPelletPosition = ECS_GetPosition(powerPelletEntity);
          powerPelletPosition->row = row;
          powerPelletPosition->column = column;
          Edible *powerPelletEdible = ECS_GetEdible(powerPelletEntity);
          powerPelletEdible->scoreValue = POWER_PELLET_SCORE_VALUE;
          powerPelletEdible->typeEaten = POWER_PELLET;
          levelData->mapTiles[row][column] = TILE_EMPTY;
          break;
        }
        default: {
          levelData->mapTiles[row][column] = mapTile;
          break;
        }
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
      MapTile newMapTile = levelData->mapTiles[row][col];
      tileRect.x = col * MAP_GRID_CELL_SIZE;
      tileRect.y = (row * MAP_GRID_CELL_SIZE) + UI_BLACK_BAR_HEIGHT;
      switch (newMapTile) {
      case TILE_WALL:
        // Walls are Blue
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &tileRect);
        break;
      case TILE_GHOST_DOOR:
        // Ghost Door is Pink
        // TODO: Look at official Pac-Man game and make it whatever the game
        // actually is
        GraphicsDrawTile(renderer, TILE_GHOST_DOOR, tileRect.x, tileRect.y);
        break;
      case TILE_FRUIT:
        // Fruit is orange for now. For testing purposes only
        // TODO: Make each fruit it's own fruit entity rather than just a
        // marker on the map.
        SDL_SetRenderDrawColor(renderer, 255, 154, 51, 255);
        break;
      case TILE_EMPTY:
        // Empty space will be all black
        // TODO: Fix it so when empty space can be used to move through
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        break;
      default:
        break;
      }
    }
  }
}
MapTile GetMapTile(LevelData *levelData, int row, int col) {
  MapTile someMapTile = levelData->mapTiles[row][col];
  return someMapTile;
}
void SetMapTile(LevelData *levelData, int row, int col, MapTile newTile) {
  levelData->mapTiles[row][col] = newTile;
}
