set -e

PROJECT_NAME=main
PROJECT_FILES="../src/*.c"
PROJECT_INCLUDES="../src/"
FLAGS="-Wall -Wextra -std=c11 -pedantic -ggdb -lSDL2 -lSDL2_ttf"
LIBS='sdl2 sdl2_ttf'

if [ ! -d ./build ]; then
    mkdir ./build
fi
if [ `uname` = "Darwin" ]; then
    FLAGS+=" -framework OpenGL"
fi

# copy fonts dir
if [ ! -d ./build/fonts ]; then
    cp -r ./fonts ./build/
fi

pushd ./build
clang $FLAGS $PROJECT_FILES -o$PROJECT_NAME -I$PROJECT_INCLUDES `pkg-config --cflags --libs $LIBS`
popd
