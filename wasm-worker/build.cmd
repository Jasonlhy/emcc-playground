@REM emcc --clear-cache
emcc -g -sWASM_WORKERS -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS="[""png""]" -s FETCH --preload-file ../resources@/ -o main.html main.cpp