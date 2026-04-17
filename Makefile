#OBJS specifies which files to compile as part of the project
OBJS = src/main.c
#OBJ_Name specifies the name of the executable
OBJ_Name = hac_man_summer_project
# COMPILER_FLAGS specifies the additional compilation options
COMPILER_FLAGS = -w 

# LINKER_FLAGS specifies the libraries the project is linking
LINKER_FLAGS = -lSDL2 -lm -lSDL2_image -lSDL2_audio -lSDL2_mixer -lSDL2_ttf

# COMPILER specifies the compiler
COMPILER = gcc

all: $(OBJS)
	$(COMPILER) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_Name)

clean: 
	rm $(OBJ_Name)
                              