#include <SDL2/SDL.h>
#include <main_base.h>
#include <main_platform.h>

// Returns new platform
Platform create_platform(Sint32 x, Sint32 y, Sint32 w, Sint32 h, SDL_Color color)
{
 return (Platform)
 {
  .rect = {x, y, w, h},
  .color = { color.r, color.g, color.b, color.a },
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
