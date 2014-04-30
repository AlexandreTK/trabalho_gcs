CC = clang++
CFLAGS = -Wall -W -ansi -pedantic -Wno-unused-parameter -g -I./include/ `sdl2-config --cflags --libs` -lSDL2_image

SOURCE = src/main.cpp src/window.cpp src/character.cpp src/texture.cpp

.PHONY: clean

KATW:
	$(CC) -o $@ $(SOURCE) $(CFLAGS)

clean:
	@rm -f KATW
