@REM emcc -g --bind -s FETCH -o testfetch.html testfetch.cpp
emcc -g --bind -s FETCH -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=4 -o testfetch.html testfetch.cpp