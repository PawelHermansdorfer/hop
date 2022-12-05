@echo off


curl -fsSL -o SDL2-devel-2.24.0-VC.zip https://github.com/libsdl-org/SDL/releases/download/release-2.24.0/SDL2-devel-2.24.0-VC.zip 
curl -fsSL -o SDL2_ttf-devel-2.20.1-VC.zip https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.1/SDL2_ttf-devel-2.20.1-VC.zip 

tar -xf SDL2-devel-2.24.0-VC.zip
tar -xf SDL2_ttf-devel-2.20.1-VC.zip

if not exist dependencies\ mkdir dependencies\

move SDL2-2.24.0 dependencies\SDL2

del SDL2-devel-2.24.0-VC.zip 
if not exist dependencies\SDL2\temp\ mkdir dependencies\SDL2\temp\
move dependencies\SDL2\include dependencies\SDL2\temp\SDL2
move dependencies\SDL2\temp dependencies\SDL2\include
