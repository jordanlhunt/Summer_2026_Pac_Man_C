# SRCS specifies which files to compile as part of the project
SRCS = src/main.c \
       src/core/gamecontext.c \
       src/core/input.c \
       src/core/leveldata.c \
       src/ecs/ecs.c \
       src/ecs/entities/entity.c \
       src/map/map.c \
       src/systems/collisionSystem.c \
       src/systems/movementSystem.c \
       src/systems/inputSystem.c \
       src/systems/renderSystem.c \
       src/systems/ghostSystem.c \
       src/core/gameinitialization.c

# COMPILER specifies the compiler
COMPILER = gcc

# COMPILER_FLAGS specifies the additional compilation options
COMPILER_FLAGS = -Wall -Wextra -Werror=implicit-function-declaration

# Include flags
INCLUDE_FLAGS = -I./include

# Debug flags
DEBUG_FLAGS = -g -O0

# --- OS DETECTION & CONDITIONAL FLAGS ---
ifeq ($(OS),Windows_NT)
    # Windows (MinGW) Specifics
    OBJ_Name = hac_man_summer_project.exe
    LIBRARY_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
    CLEAN_CMD = rm -f $(OBJ_Name)
else
    # Linux Specifics
    OBJ_Name = hac_man_summer_project
    LIBRARY_FLAGS = -lSDL2 -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf
    CLEAN_CMD = rm -f $(OBJ_Name)
endif


OBJS = $(SRCS)

.PHONY: all clean debug

all: $(OBJS)
	$(COMPILER) $(OBJS) $(INCLUDE_FLAGS) $(COMPILER_FLAGS) $(LIBRARY_FLAGS) -o $(OBJ_Name)

debug: $(OBJS)
	$(COMPILER) $(OBJS) $(INCLUDE_FLAGS) $(COMPILER_FLAGS) $(DEBUG_FLAGS) $(LIBRARY_FLAGS) -o $(OBJ_Name)

clean:
	$(CLEAN_CMD)
