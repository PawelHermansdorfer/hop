#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL.h>

#define PLATFORM_INIT_SPEED 5
#define PLATFORM_MINIMAL_SIZE 100

#define PLATFORM_SPAWN_NONE 0
#define PLATFORM_SPAWN_BORDER 1
#define PLATFORM_SPAWN_CENTER 2

typedef struct {
  SDL_Rect rect;
  SDL_Color color;
  float velocity;
} Platform;

typedef struct {
  Uint8 lastSpawn;
} PlatformHandler;

Platform create_platform(Sint32 x, Sint32 y, Sint32 w);
PlatformHandler create_platform_handler();
void platform_render(Platform *platform, SDL_Renderer *renderer);
void platform_update(Platform *platform);
void reset_platform(Platform *platform, PlatformHandler *platform_handler);

#endif // PLATFORM_H
