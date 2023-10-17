#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} sdl_t;

typedef struct {
    uint32_t window_width;
    uint32_t window_height;
    uint32_t fg_color;
    uint32_t bg_color;
    uint32_t scale_factor;
} config_t;

bool init_sdl(sdl_t *sdl, const config_t config) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    sdl->window = SDL_CreateWindow("Chip-8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.window_width * config.scale_factor, config.window_height * config.scale_factor, 0);
    if (!(sdl->window)) {
        SDL_Log("Unable to create window: %s\n", SDL_GetError());
        return false;
    }

    sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
    if (!(sdl->renderer)) {
        SDL_Log("Unable to create renderer: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool set_config_from_args(config_t *config, const int argc, char **argv) {
    // defaults 
    *config = (config_t) {
        .window_width = 64, // chip-8 width
        .window_height = 32, // chip-8 height
        .fg_color = 0xFFFFFFFF, // white
        .bg_color = 0xFFFF00FF, // yellow
        .scale_factor = 20
    };

    // overrides
    for (int i = 1; i < argc; i++) {
        (void) argv[i];
        // ...
    }

    return true;
}

void final_cleanup(const sdl_t sdl) {
    SDL_DestroyRenderer(sdl.renderer);
    SDL_DestroyWindow(sdl.window);
    SDL_Quit();
}

void clear_window(const sdl_t sdl, const config_t config) {
    const uint8_t r = (config.bg_color >> 24) & 0xFF;
    const uint8_t g = (config.bg_color >> 16) & 0xFF;
    const uint8_t b = (config.bg_color >> 8) & 0xFF;
    const uint8_t a = (config.bg_color >> 0) & 0xFF;

    SDL_SetRenderDrawColor(sdl.renderer, r, g, b, a);
    SDL_RenderClear(sdl.renderer);
}

void update_screen(const sdl_t sdl) {
    SDL_RenderPresent(sdl.renderer);
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
    if (!(init_sdl(&sdl, config))) {
        exit(EXIT_FAILURE);
    } else {
        puts("SDL initialized successfully! Cleaning up...");
    }

    // main emulator loop
    while (true) {
        // get_time();
        // Emulate chip-8 instructions
        // get_time() since last get_time();

        // SDL_Delay(16.67 - actual time elapsed);
        SDL_Delay(16); // approx 60 fps
        update_screen(sdl);
    }

    // initial window clear
    clear_window(sdl, config);

    // final cleanup
    final_cleanup(sdl);
    puts("Cleaned up. Goodbye!");
    exit(EXIT_SUCCESS);
}