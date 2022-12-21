#include <emscripten/wasm_worker.h>
#include <stdio.h>
#include "SDL_image.h"
#include <emscripten/fetch.h>

void fetch()
{
  const char* url = "http://localhost:5000/111.png";

  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "GET");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_SYNCHRONOUS;
  emscripten_fetch_t *fetch = emscripten_fetch(&attr, url); // Blocks here until the operation is complete.
  if (fetch->status == 200)
  {
    printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
    // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
  }
  else
  {
    printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
  }
  emscripten_fetch_close(fetch);
}

void load_image()
{
  printf("before load_image\n");
  fetch();
  printf("after load_image\n");
  // abort();

  // const char *file = "111.png";
  // SDL_Surface *surface = IMG_Load(file);
  // if (!surface)
  // {
  //   printf("  SDL_Image load error: %s\n", IMG_GetError());
  // }
  // else
  // {
  //   printf("SDL_Image loaded\n");
  // }
}

void run_in_worker()
{
  printf("Hello from wasm worker!\n");
  load_image();
}

void main_loop()
{
  static int initialized = 0;
  if (!initialized)
  {
    printf("main_loop init\n");

    emscripten_wasm_worker_t worker = emscripten_malloc_wasm_worker(/*stack size: */ 1024);
    emscripten_wasm_worker_post_function_v(worker, run_in_worker);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
      abort();

    initialized = 1;
  }
}

int main()
{
  printf("hellow orld\n");
  emscripten_set_main_loop(main_loop, 0, 1);

  return 0;
}