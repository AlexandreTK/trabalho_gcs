CC = clang++
CFLAGS = -Wall -W -ansi -pedantic -g -I./include/ -O2 `sdl2-config --cflags`
LIBS = `sdl2-config --libs`

SDL_FLAGS = `sdl2-config --cflags --libs` -lSDL2_image

SRC_DIR = src

MOD_DIR = mod

.PHONY: clean 

FULL_MODS = $(MOD_DIR)/Main.o $(MOD_DIR)/Game.o $(MOD_DIR)/TextureManager.o

KATW: Game.o Main.o TextureManager.o
	$(CC) -o $@ $(FULL_MODS) $(CFLAGS) $(SDL_FLAGS)

Main.o: mkdir_mod $(SRC_DIR)/Main.cpp
	$(CC) -c $(SRC_DIR)/Main.cpp $(CFLAGS) $(SDL_FLAGS) -o $(MOD_DIR)/$@

Game.o: mkdir_mod $(SRC_DIR)/Game.cpp
	$(CC) -c $(SRC_DIR)/Game.cpp $(CFLAGS) $(SDL_FLAGS) -o $(MOD_DIR)/$@

TextureManager.o: mkdir_mod $(SRC_DIR)/TextureManager.cpp
	$(CC) -c $(SRC_DIR)/TextureManager.cpp $(CFLAGS) $(SDL_FLAGS) -o $(MOD_DIR)/$@

mkdir_mod:
	@mkdir -p $(MOD_DIR)

clean:
	@rm -f $(MOD_DIR)/*
	@rm -f KATW
