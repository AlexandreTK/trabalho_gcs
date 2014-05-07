CC = clang++
CFLAGS = -Wall -W -ansi -pedantic -Wno-unused-parameter -g -I./include/ -O2

SDL_FLAGS = `sdl2-config --cflags --libs` -lSDL2_image

SRC_DIR = src

MOD_DIR = mod

.PHONY: clean main.o game.o mkdir_mod

FULL_MODS = $(MOD_DIR)/main.o $(MOD_DIR)/game.o

KATW: mkdir_mod clean game.o main.o
	$(CC) -o $@ $(FULL_MODS) $(CFLAGS) $(SDL_FLAGS)

main.o: mkdir_mod $(SRC_DIR)/main.cpp
	$(CC) -c src/main.cpp $(CFLAGS) $(SDL_FLAGS) -o $(MOD_DIR)/$@

game.o: mkdir_mod $(SRC_DIR)/game.cpp
	$(CC) -c src/game.cpp $(CFLAGS) $(SDL_FLAGS) -o $(MOD_DIR)/$@

mkdir_mod:
	@mkdir -p $(MOD_DIR)

clean:
	@rm -f KATW
