#include <SDL2/SDL.h>
#include <stdio.h>

#include <functions.h>

void scc(int error_code) {
 if (error_code < 0) {
  printf("SDL ERROR: %s\n", SDL_GetError());
  exit(1);
 }
}

void *scp(void *ptr) {
 if(ptr == NULL) {
  printf("SDL ERROR: %s\n", SDL_GetError());
 }
 return ptr;
}
