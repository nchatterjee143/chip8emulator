CFLAGS=-std=c99 -Wall -Wextra -Werror
LDFLAGS=-L/opt/homebrew/opt/sdl2/lib -lSDL2
INCLUDES=-I/opt/homebrew/opt/sdl2/include

release: chip8.c
	gcc chip8.c -o chip8emulator $(CFLAGS) $(LDFLAGS) $(INCLUDES)

clean:
	rm -rf chip8emulator