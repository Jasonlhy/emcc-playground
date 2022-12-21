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


void* ThreadFun(void* arg)
{
  printf("Hello from pthread!\n");
  load_image();
  return NULL;
}


int main() {
    pthread_t loadTaskThread;
    int res = pthread_create(&loadTaskThread, NULL, ThreadFun, NULL);
    if (res != 0) {
        printf("Failed to create res\n");
    }

    return 0;
}