#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#if WINDOWS
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL_ttf.h>
#endif

typedef struct {
  SDL_Texture *texture;
  TTF_Font *font;
  SDL_Color color;
  SDL_Rect srcrect;
  SDL_Rect dstrect;
  Uint8 centered;
} Text;

Text create_text(Sint16 x, Sint16 y, const char *text, SDL_Color color,
                 Uint8 font_size, SDL_Renderer *renderer);
void update_text(Text *text, const char *new_text, SDL_Renderer *renderer);
void render_text(Text *text, SDL_Renderer *renderer);
void free_text(Text *text);

#endif // TEXT_H
