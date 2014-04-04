CC = clang++
CFLAGS = -lSDL2 -Wall -W -ansi -pedantic -Wno-unused-parameter -I/usr/include/SDL2/

SOURCE = src/main.cpp src/window.cpp

.PHONY: clean

KATW:
	$(CC) -o $@ $(SOURCE) $(CFLAGS)

clean:
	@rm -f KATW
