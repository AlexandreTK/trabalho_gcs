CC = clang++
CFLAGS = -Wall -W -Wno-unused-private-field -Wno-unused-parameter -Wno-reorder -Wno-delete-non-virtual-dtor -ansi -pedantic -g -Iinclude/ -O2
SDL_FLAGS = `sdl2-config --cflags`
SDL_LIBS = `sdl2-config --libs` -lSDL2_image

SRC_DIR = src
OBJ_DIR = obj

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(basename $(notdir $(SOURCES)))))

.PHONY: clean mkdir_mod

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(SDL_FLAGS)

all: 
	@mkdir -p $(OBJ_DIR)
	@make KATW

KATW:  $(OBJS)
	$(CC) -o $@ $(OBJS) $(SDL_LIBS)

clean:
	@rm -f $(OBJ_DIR)/*
	@rm -f KATW
