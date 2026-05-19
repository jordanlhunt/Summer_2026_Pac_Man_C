#SRCS specifies which files to compile as part of the project
SRCS = src/main.c \
       src/core/audio.c \
       src/core/gamecontext.c \
       src/core/gamestate.c \
       src/core/graphics.c \
       src/core/input.c \
       src/core/leveldata.c \
       src/ecs/ecs.c \
       src/ecs/entities/entity.c \
       src/map/map.c \
       src/systems/collisionSystem.c \
       src/systems/movementSystem.c \
       src/systems/inputSystem.c \
       src/systems/renderSystem.c \
       src/core/gameinitialization.c
#OBJ_Name specifies the name of the executable
OBJ_Name = hac_man_summer_project
# COMPILER_FLAGS specifies the additional compilation options
COMPILER_FLAGS = -Wall -Wextra -Werror=implicit-function-declaration
# LIBRARY_FLAGS specifies the libraries the project is linking
LIBRARY_FLAGS = -lSDL2 -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
# COMPILER specifies the compiler
COMPILER = gcc
# Debug flags
DEBUG_FLAGS = -g -O0
#Include flags
INCLUDE_FLAGS = -I./include 
OBJS = $(SRCS)
.PHONY: all clean debug
all: $(OBJS)
	$(COMPILER) $(OBJS) $(INCLUDE_FLAGS) $(COMPILER_FLAGS) $(LIBRARY_FLAGS) -o $(OBJ_Name)
debug: $(OBJS)
	$(COMPILER) $(OBJS) $(INCLUDE_FLAGS) $(COMPILER_FLAGS) $(DEBUG_FLAGS) $(LIBRARY_FLAGS) -o $(OBJ_Name)
clean: 
	rm -f $(OBJ_Name)
