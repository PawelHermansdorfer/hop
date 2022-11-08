#include <SDL2/SDL.h>
#include <main_base.h>
#include <main_platform.h>

// Returns new platform
Platform create_platform(Sint32 x, Sint32 y, Sint32 w)
{
 return (Platform)
 {
  .rect = {x, y, w, PLATFORM_HEIGHT},
  .color = { PLATFORM_COLOR_RED, PLATFORM_COLOR_GREEN, PLATFORM_COLOR_BLUE, PLATFORM_COLOR_ALPHA },
  .type = PLATFORM_TYPE_GROUND
 };
}

// Creates lava at the bottom of the screen
Platform create_lava(void)
{
 return (Platform)
 {
  .rect = {LAVA_POS_X, LAVA_POS_Y, LAVA_WIDTH, LAVA_HEIGHT},
  .color = {LAVA_COLOR_RED, LAVA_COLOR_GREEN, LAVA_COLOR_BLUE, LAVA_COLOR_ALPHA},
  .type = PLATFORM_TYPE_LAVA
 };
}

void platform_render(Platform *platform, SDL_Renderer *renderer)
{
  scc(SDL_SetRenderDrawColor(
   renderer,
   platform->color.r,
   platform->color.g,
   platform->color.b,
   platform->color.a
  ));
  scc(SDL_RenderFillRect(renderer, &platform->rect));
}
