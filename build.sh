set -e

if [ ! -d ./build ]; then
    mkdir ./build
fi

PROJECT_NAME=main
PROJECT_FILES="../src/*.c"
PROJECT_INCLUDES="../src/"

pushd ./build
clang $PROJECT_FILES -o main -I$PROJECT_INCLUDES `pkg-config --libs --cflags sdl2`
popd
