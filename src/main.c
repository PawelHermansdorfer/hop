#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#include <main_base.h>
#include <main_vectors.h>
#include <main_platform.h>
#include <main_fire.h>
#include <main_agent.h>



int main(int argc, char *argv[])
{
 // Init SDL2
 scc(SDL_Init(SDL_INIT_VIDEO));

 SDL_Window *window = scp(SDL_CreateWindow("Window", 100, 100, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_RESIZABLE));
 SDL_Renderer *renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
 scc(SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND));

 // Create main character struct
 Agent hero = create_agent(DISPLAY_WIDTH/2 - AGENT_WIDTH/2, DISPLAY_HEIGHT/2 - AGENT_WIDTH/2);

 // Create fire
 Fire fire = create_fire();

 // Create ground
 Platform platforms[NUMBER_OF_PLATFORMS] = {create_platform(0, 450, 400),
                                            create_platform(DISPLAY_WIDTH-400, 600, 400),
                                            create_platform(200, 300, DISPLAY_WIDTH-400),
                                            };

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
   BG_COLOR_BLUE,
   BG_COLOR_GREEN,
   BG_COLOR_ALPHA
   ));
  scc(SDL_RenderClear(renderer));

  // Update hero
  agent_move(&hero, kb[SDL_SCANCODE_D] + -kb[SDL_SCANCODE_A]);
  if (kb[SDL_SCANCODE_SPACE])
  {
   agent_jump(&hero);
  }
  agent_update(&hero);
  agent_collide_border(&hero);

  for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
  {
   agent_collide_platform(&hero, &platforms[i]);
  }
  // Update ground
  for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
  {
   platform_render(&platforms[i], renderer);
  }
  agent_render(&hero, renderer);

  // Update and draw fire
  fire_draw(&fire, renderer);
  fire_update(&fire);


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
