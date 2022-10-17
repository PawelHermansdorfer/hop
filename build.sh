set -e

PROJECT_NAME=main
PROJECT_FILES="../src/*.c"
PROJECT_INCLUDES="../src/"
FLAGS="-Wall -Wextra -std=c11 -pedantic -ggdb"
LIBS='sdl2 glew'

if [ ! -d ./build ]; then
    mkdir ./build
fi
if [ `uname` = "Darwin" ]; then
    FLAGS+=" -framework OpenGL"
fi


pushd ./build
clang $FLAGS $PROJECT_FILES -o$PROJECT_NAME -I$PROJECT_INCLUDES `pkg-config --libs $LIBS`
popd



# CC="${CXX:-cc}"
# PKGS="sdl2 glew freetype2"
# CFLAGS="-Wall -Wextra -std=c11 -pedantic -ggdb"
# LIBS=-lm
# SRC="src/main.c src/la.c src/editor.c src/sdl_extra.c src/file.c src/gl_extra.c src/free_glyph.c src/cursor_renderer.c src/uniforms.c"
# 
# if [ `uname` = "Darwin" ]; then
#     CFLAGS+=" -framework OpenGL"
# fi
# 
# $CC $CFLAGS `pkg-config --cflags $PKGS` -o ded $SRC $LIBS `pkg-config --libs $PKGS`

