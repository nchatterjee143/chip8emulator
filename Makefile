CFLAGS=-std=c17 -Wall -Wextra -Werror

chip8emu: chip8.c
	gcc chip8.c -o chip8 $(CFLAGS) -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2