#ifndef PLATFORM_H
#define PLATFORM_H


#define PLATFORM_TYPE_LAVA 0
#define PLATFORM_TYPE_GROUND 1

typedef struct
{
 SDL_Rect rect;
 SDL_Color color;
 Uint8 type;
}
Platform;

Platform create_platform(Sint32 x, Sint32 y, Sint32 w);
Platform create_lava(void);
void platform_render(Platform *platform, SDL_Renderer *renderer);

#endif // PLATFORM_H
