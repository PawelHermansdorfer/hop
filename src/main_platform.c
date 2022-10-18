#include <SDL2/SDL.h>
#include <main_platform.h>

// Returns new platform
Platform create_platform(Uint32 x, Uint32 y, Uint32 w, Uint32 h)
{
 return (Platform)
 {
  .rect = {x, y, w, h},
  .color = { PLATFORM_COLOR_RED, PLATFORM_COLOR_GREEN, PLATFORM_COLOR_BLUE, PLATFORM_COLOR_ALPHA },
 };
}
