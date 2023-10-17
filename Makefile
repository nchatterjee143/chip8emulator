CFLAGS=-std=c17 -Wall -Wextra -Werror

chip8emulator: chip8.c
	gcc chip8.c -o chip8emulator $(CFLAGS) -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2