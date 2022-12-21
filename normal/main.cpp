#include <emscripten/wasm_worker.h>
#include <stdio.h>
#include "SDL_image.h"


void load_image() {
    const char* file = "111.png";
    SDL_Surface* surface = IMG_Load(file);
    if (!surface) {
        printf("  SDL_Image load error: %s\n", IMG_GetError());
    }
    else {
      printf("SDL_Image loaded\n");
    }
}

int main() {
    load_image();

    return 0;
}