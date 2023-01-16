
emcc -s MAX_WEBGL_VERSION=2 -I "..\..\Common" "MipMap2D.c" "..\..\Common\esShader.c" "..\..\Common\esTransform.c" "..\..\Common\esShapes.c" "..\..\Common\esUtil.c" -o MipMap2D.html