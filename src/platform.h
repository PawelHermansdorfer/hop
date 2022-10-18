#ifndef PLATFORM_H
#define PLATFORM_H

#define PLATFORM_COLOR_RED 255
#define PLATFORM_COLOR_GREEN 255
#define PLATFORM_COLOR_BLUE 255
#define PLATFORM_COLOR_ALPHA 255

typedef struct
{
 SDL_Rect rect;
 SDL_Color color;
}
Platform;

Platform create_platform(Uint32 x, Uint32 y, Uint32 w, Uint32 h);

#endif // PLATFORM_H
