#include <SDL.h>

#include <main_base.h>
#include <main_platform.h>

// Returns new platform
Platform create_platform(Sint32 x, Sint32 y, Sint32 w) {
  return (Platform){.rect = {x, y, w, PLATFORM_HEIGHT},
                    .color = {PLATFORM_COLOR_RED, PLATFORM_COLOR_GREEN,
                              PLATFORM_COLOR_BLUE, PLATFORM_COLOR_ALPHA},
                    .velocity = PLATFORM_INIT_SPEED};
}

PlatformHandler create_platform_handler() {
  return (PlatformHandler){PLATFORM_SPAWN_NONE};
}

void platform_render(Platform *platform, SDL_Renderer *renderer) {
  scc(SDL_SetRenderDrawColor(renderer, platform->color.r, platform->color.g,
                             platform->color.b, platform->color.a));
  scc(SDL_RenderFillRect(renderer, &platform->rect));
}

void platform_update(Platform *platform) {
  platform->rect.y += platform->velocity;
}

void reset_platform(Platform *platform, PlatformHandler *platform_handler) {
  platform->rect.y = -350;

  if (platform_handler->lastSpawn == PLATFORM_SPAWN_NONE) {
    platform->rect.w = PLATFORM_MINIMAL_SIZE + (rand() % 300);
    platform->rect.x = rand() % (DISPLAY_WIDTH - platform->rect.w);

    if ((DISPLAY_WIDTH / 2) - platform->rect.x < (DISPLAY_WIDTH / 4)) {
      platform_handler->lastSpawn = PLATFORM_SPAWN_CENTER;
    } else {
      platform_handler->lastSpawn = PLATFORM_SPAWN_BORDER;
    }
  }

  else if (platform_handler->lastSpawn == PLATFORM_SPAWN_BORDER) {
    platform->rect.w = PLATFORM_MINIMAL_SIZE + (rand() % 300);
    platform->rect.x = (DISPLAY_WIDTH / 2) - (platform->rect.w / 2);

    platform_handler->lastSpawn = PLATFORM_SPAWN_CENTER;
  }

  else if (platform_handler->lastSpawn == PLATFORM_SPAWN_CENTER) {
    platform->rect.w = PLATFORM_MINIMAL_SIZE + (rand() % 300);

    int rnd = rand() % 2;
    if (rnd == 0) {
      platform->rect.x = 0;
    } else {
      platform->rect.x = DISPLAY_WIDTH - platform->rect.w;
    }

    platform_handler->lastSpawn = PLATFORM_SPAWN_BORDER;
  }
}
