CC = clang++
CFLAGS = -Wall -W -ansi -pedantic -Wno-unused-parameter -g -I./include/ -O2

SDL_FLAGS = `sdl2-config --cflags --libs`

SRC_DIR = src

MOD_DIR = mod

.PHONY: clean main.o game.o mkdir_mod

FULL_MODS = $(MOD_DIR)/main.o $(MOD_DIR)/game.o

KATW: game.o main.o
	@$(CC) -o $@ $(FULL_MODS) $(CFLAGS) $(SDL_FLAGS)

main.o: mkdir_mod $(SRC_DIR)/Main.cpp
	@$(CC) -c $(SRC_DIR)/Main.cpp $(CFLAGS) $(SDL_FLAGS) -o $(MOD_DIR)/$@

game.o: mkdir_mod $(SRC_DIR)/Game.cpp
	@$(CC) -c $(SRC_DIR)/Game.cpp $(CFLAGS) $(SDL_FLAGS) -o $(MOD_DIR)/$@

mkdir_mod:
	@mkdir -p $(MOD_DIR)

clean:
	@rm -f $(MOD_DIR)/*
	@rm -f KATW
