#OBJS specifies which files to compile as part of the project
OBJS = src/main.c src/core/audio.c src/core/entity.c src/core/gamecontext.c src/core/gamestate.c src/core/graphics.c src/core/input.c src/core/leveldata.c src/core/player.c src/map/map.c
#OBJ_Name specifies the name of the executable
OBJ_Name = hac_man_summer_project
# COMPILER_FLAGS specifies the additional compilation options
COMPILER_FLAGS = -w 

# LINKER_FLAGS specifies the libraries the project is linking
LINKER_FLAGS = -lSDL2 -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf 

# COMPILER specifies the compiler
COMPILER = gcc

# Debug flags
DEBUG_FLAGS = -g -O0

.PHONY: all clean

all: $(OBJS)
	$(COMPILER) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_Name)

debug: $(OBJS)
	$(COMPILER) $(OBJS) $(COMPILER_FLAGS) $(DEBUG_FLAGS) $(LINKER_FLAGS) -o $(OBJ_Name)

clean: 
	rm -f $(OBJ_Name)
