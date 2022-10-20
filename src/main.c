#include <SDL2/SDL.h>
#include <stdio.h>

#include <main_base.h>
#include <main_vectors.h>
#include <main_platform.h>
#include <main_agent.h>


int main(int argc, char *argv[])
{
 // Init SDL2
 scc(SDL_Init(SDL_INIT_VIDEO));

 SDL_Window *window = scp(SDL_CreateWindow("Window", 100, 100, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_RESIZABLE));
 SDL_Renderer *renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

 // Create main character struct
 Sint32 hero_x = DISPLAY_WIDTH/2 - AGENT_WIDTH/2;
 Sint32 hero_y = DISPLAY_HEIGHT/2 - AGENT_WIDTH/2;
 SDL_Color hero_color = {
  HERO_COLOR_RED,
  HERO_COLOR_GREEN,
  HERO_COLOR_BLUE,
  HERO_COLOR_ALPHA,
 };
 Agent hero = create_agent(hero_x, hero_y, HERO_WIDTH, HERO_HEIGHT, hero_color);

 // Create ground
 SDL_Color ground_color = {
 GROUND_COLOR_RED,
 GROUND_COLOR_GREEN,
 GROUND_COLOR_BLUE,
 GROUND_COLOR_ALPHA,
 };
 Sint32 ground_x = 0;
 Sint32 ground_y = DISPLAY_HEIGHT - GROUND_WIDTH;
 // NOTE: Make ground smaller for debug
 Platform ground = create_platform(ground_x, ground_y, DISPLAY_WIDTH, GROUND_WIDTH, ground_color);

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

    // X button click
    case SDL_QUIT:
     quit = 1;
     break;
   }
  }

  // Handle user inputs
  const Uint8 *kb = SDL_GetKeyboardState(NULL);

  // Draw background
  scc(SDL_SetRenderDrawColor(
   renderer,
   BG_COLOR_RED,
   BG_COLOR_GREEN,
   BG_COLOR_BLUE,
   BG_COLOR_ALPHA
   ));
  scc(SDL_RenderClear(renderer));

  // Update hero
  agent_move(&hero, kb[SDL_SCANCODE_D] + -kb[SDL_SCANCODE_A]);
  agent_update(&hero);
  agent_collide_platform(&hero, &ground);
  if (kb[SDL_SCANCODE_SPACE])
  {
   agent_jump(&hero);
  }
  agent_render(&hero, renderer);

  // Update ground
  platform_render(&ground, renderer);

  // Render scene
  SDL_RenderPresent(renderer);


  // Get time of end of the frame
  Uint64 end_time = SDL_GetPerformanceCounter();

// TODO(Aa_Pawelek): MAKE FRAME_RATE macro, 1/FPS * 100 instead of 16.6...f
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
