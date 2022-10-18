#include <SDL2/SDL.h>
#include <stdio.h>

#include <functions.h>
#include <vectors.h>
#include <hero.h>

int main(int argc, char *argv[])
{
 // Init SDL2
 scc(SDL_Init(SDL_INIT_VIDEO));

 SDL_Window *window = scp(SDL_CreateWindow("Window", 100, 100, 800, 600, SDL_WINDOW_RESIZABLE));
 SDL_Renderer *renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

 // Create main character struct
 Character hero = CreateHero();

 Uint8 quit = 0;
 SDL_Event event = {0};

 // Main game loop
 while (!quit)
 {
  // Time of beginning of the frame
  Uint64 start_time = SDL_GetPerformanceCounter();

  // Handle events
  while (SDL_PollEvent(&event))
  {
   switch (event.type)
   {
    // ESC key
    case SDL_KEYDOWN:
     switch (event.key.keysym.sym)
     {
      case SDLK_ESCAPE:
       quit = 1;
       break;
     }
     break;

    // X click
    case SDL_QUIT:
     quit = 1;
     break;
   }
  }

  // Handle user inputs
  const Uint8 *kb = SDL_GetKeyboardState(NULL);

  // Draw background
  scc(SDL_SetRenderDrawColor(renderer, 3, 3, 3, 0));
  scc(SDL_RenderClear(renderer));

  // Update hero
  scc(SDL_SetRenderDrawColor(renderer, 120, 220, 240, 0));
  MoveCharacter(&hero, kb[SDL_SCANCODE_D] + -kb[SDL_SCANCODE_A]);
  update_character(&hero);
  scc(SDL_RenderFillRect(renderer, &hero.rect));

  // Render scene
  SDL_RenderPresent(renderer);


  // Get time of end of the frame
  Uint64 end_time = SDL_GetPerformanceCounter();

  // Capping frame rate
  float elapsedMS = (end_time - start_time) / (float)SDL_GetPerformanceFrequency() * 100.0f;
  if (elapsedMS < 16.666666f)
  {
   SDL_Delay(floor(16.666666f - elapsedMS));
  }
 }

 SDL_Quit();
 return 0;
}
