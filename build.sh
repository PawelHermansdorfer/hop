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
