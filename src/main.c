#include <SDL2/SDL.h>
#include <stdio.h>

void scc(int error_code)
{
 if (error_code < 0)
 {
  printf("SDL ERROR: %s\n", SDL_GetError());
  exit(1);
 }
}

void *scp(void *ptr)
{
 if(ptr == NULL)
 {
  printf("SDL ERROR: %s\n", SDL_GetError());
 }
 return ptr;
}

int main(int argc, char *argv[])
{
 scc(SDL_Init(SDL_INIT_VIDEO));

 SDL_Window *window = scp(SDL_CreateWindow("Window", 100, 100, 800, 600, SDL_WINDOW_RESIZABLE));
 SDL_Renderer *renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

 char quit = 0;
 while (!quit)
 {
  SDL_Event event = {0};
  while (SDL_PollEvent(&event))
  {
   switch(event.type)
   {
    case SDL_QUIT:
    {
     quit = 1;
    } break;
   }
  }

  scc(SDL_SetRenderDrawColor(renderer, 3, 3, 3, 0));
  scc(SDL_RenderClear(renderer));
  SDL_RenderPresent(renderer);
 }

 SDL_Quit();
 return 0;
}