@REM emcc --clear-cache
emcc -g -s USE_PTHREADS=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS="[""png""]" --preload-file ../resources@/ -o main.html main.cpp