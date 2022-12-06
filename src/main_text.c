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

  SDL_Rect srcrect = (SDL_Rect){0, 0, text_surface->w, text_surface->h};

  SDL_Rect dstrect;
  Uint8 centered;
  if (x == -1) {
    dstrect = (SDL_Rect){(DISPLAY_WIDTH / 2) - (text_surface->w / 2), y,
                         text_surface->w, text_surface->h};
    centered = 1;
  } else {
    dstrect = (SDL_Rect){x, y, text_surface->w, text_surface->h};
    centered = 0;
  }

  SDL_FreeSurface(text_surface);

  return (Text){
      .texture = text_texture,
      .font = font,
      .color = color,
      .srcrect = srcrect,
      .dstrect = dstrect,
      .centered = centered,
  };
}

void update_text(Text *text, const char *new_text, SDL_Renderer *renderer) {
  SDL_Surface *new_surface =
      scp(TTF_RenderText_Solid(text->font, new_text, text->color));
  SDL_DestroyTexture(text->texture);
  text->texture = scp(SDL_CreateTextureFromSurface(renderer, new_surface));

  text->srcrect.w = new_surface->w;
  text->srcrect.h = new_surface->h;

  if (text->centered) {
    text->dstrect.x = (DISPLAY_WIDTH / 2) - (new_surface->w / 2);
  }
  text->dstrect.w = new_surface->w;
  text->dstrect.h = new_surface->h;

  SDL_FreeSurface(new_surface);
}

void render_text(Text *text, SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, text->texture, &text->srcrect, &text->dstrect);
}

void free_text(Text *text) { SDL_DestroyTexture(text->texture); }
