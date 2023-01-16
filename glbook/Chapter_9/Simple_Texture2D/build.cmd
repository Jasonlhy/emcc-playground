
@REM COMMONSRC=Common/esShader.c    \
@REM           Common/esTransform.c \
@REM           Common/esShapes.c    \
@REM           Common/esUtil.c

emcc -s MAX_WEBGL_VERSION=2 -I "..\..\Common" "Simple_Texture2D.c" "..\..\Common\esShader.c" "..\..\Common\esTransform.c" "..\..\Common\esShapes.c" "..\..\Common\esUtil.c" -o Simple_Texture2D.html