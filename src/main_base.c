#include <SDL2/SDL.h>
#include <stdio.h>

#include <main_base.h>

// SDL secured call
void scc(int error_code) {
  if (error_code < 0) {
    printf("SDL ERROR: %s\n", SDL_GetError());
    exit(1);
  }
}

// SDL secured pointer
void *scp(void *ptr) {
  if (ptr == NULL) {
    printf("SDL ERROR: %s\n", SDL_GetError());
  }
  return ptr;
}

int map(int value, int A, int B, int a, int b) {
  return (value - A) * (b - a) / (B - A) + a;
}
