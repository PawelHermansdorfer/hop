#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

typedef struct {
  SDL_Texture *texture;
  SDL_Rect rect;
} Text;

Text create_text(Sint16 x, Sint16 y, const char *text, SDL_Color color,
                 Uint8 font_size, SDL_Renderer *renderer);
void render_text(Text *text, SDL_Renderer *renderer);
void free_text(Text *text);

#endif // TEXT_H
