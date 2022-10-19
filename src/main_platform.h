#ifndef PLATFORM_H
#define PLATFORM_H

typedef struct
{
 SDL_Rect rect;
 SDL_Color color;
}
Platform;

Platform create_platform(Sint32 x, Sint32 y, Sint32 w, Sint32 h, SDL_Color color);
void platform_render(Platform *platform, SDL_Renderer *renderer);

#endif // PLATFORM_H
