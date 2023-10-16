CFLAGS=-std=c17 -Wall -Wextra -Werror

all:
	gcc chip8.c -o chip8 $(CFLAGS) -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2