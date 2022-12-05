#include <SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <main_base.h>
#include <main_text.h>

Text create_text(Sint16 x, Sint16 y, const char *text, SDL_Color color,
                 Uint8 font_size, SDL_Renderer *renderer) {

  TTF_Font *font = scp(TTF_OpenFont("./fonts/TheJewishBitmap.ttf", font_size));
  SDL_Surface *text_surface = scp(TTF_RenderText_Solid(font, text, color));

  SDL_Texture *text_texture =
      scp(SDL_CreateTextureFromSurface(renderer, text_surface));

  SDL_FreeSurface(text_surface);

  return (Text){
      .texture = text_texture,
      .rect = {x, y, text_surface->w, text_surface->h},
  };
}

void render_text(Text *text, SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, text->texture, &text->rect, &text->rect);
}

void free_text(Text *text) { SDL_DestroyTexture(text->texture); }
