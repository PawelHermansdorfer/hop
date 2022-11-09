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
