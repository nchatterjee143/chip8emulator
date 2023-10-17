#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"

typedef struct {
    SDL_Window *window;
} sdl_t;

typedef struct {
    uint32_t window_width;
    uint32_t window_height;
} config_t;

bool init_sdl(sdl_t *sdl, const config_t *config) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    sdl->window = SDL_CreateWindow("Chip-8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config->window_width, config->window_height, 0);
    if (!(sdl->window)) {
        SDL_Log("Unable to create window: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool set_config_from_args(config_t *config, const int argc, char **argv) {
    // defaults 
    config->window_width = 64;
    config->window_height = 32;

    // overrides
    for (int i = 1; i < argc; i++) {
        (void) argv[i];
        // ...
    }

    return true;
}

void final_cleanup(sdl_t *sdl) {
    SDL_DestroyWindow(sdl->window);
    SDL_Quit();
}

int main(int argc, char **argv) {
    sdl_t sdl = {0};
    config_t config = {0};
    
    // initialize configs
    if (!(set_config_from_args(&config, argc, argv))) {
        exit(EXIT_FAILURE);
    } else {
        puts("Configs initialized! Initializing SDL...");
    }
    
    // initialize SDL
    if (!(init_sdl(&sdl, &config))) {
        exit(EXIT_FAILURE);
    } else {
        puts("SDL initialized successfully! Cleaning up...");
    }

    // final cleanup
    final_cleanup(&sdl);
    puts("Cleaned up. Goodbye!");
    exit(EXIT_SUCCESS);
}