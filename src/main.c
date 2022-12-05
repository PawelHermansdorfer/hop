#include <SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <math.h>
#include <stdio.h>

#include <main_text.h>

#include <main_base.h>
#include <main_fire.h>
#include <main_platform.h>
#include <main_vectors.h>

#include <main_agent.h>

void reset_scene(Platform platforms[NUMBER_OF_PLATFORMS], Agent *hero) {
  platforms[0] = create_platform(DISPLAY_WIDTH / 2 - 150, -350, 300);
  platforms[1] = create_platform(DISPLAY_WIDTH / 2 - 200, -100, 400);
  platforms[2] = create_platform(DISPLAY_WIDTH - 400, 150, 400);
  platforms[3] = create_platform(0, 400, 300);
  platforms[4] = create_platform(0, 650, DISPLAY_WIDTH);

  *hero = create_agent(DISPLAY_WIDTH / 2 - AGENT_WIDTH / 2, 650 - AGENT_HEIGHT);
}

int main(int argc, char *argv[]) {
  // Init SDL2
  scc(SDL_Init(SDL_INIT_VIDEO));
  scc(TTF_Init());

  SDL_Window *window = scp(SDL_CreateWindow(
      "Window", 100, 100, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_RESIZABLE));
  SDL_Renderer *renderer =
      scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
  scc(SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND));

  // Create main character struct
  Agent hero =
      create_agent(DISPLAY_WIDTH / 2 - AGENT_WIDTH / 2, 650 - AGENT_HEIGHT);

  // Create fire
  Fire fire = create_fire();

  // Create ground
  Platform platforms[NUMBER_OF_PLATFORMS] = {
      create_platform(DISPLAY_WIDTH / 2 - 150, -350, 300),
      create_platform(DISPLAY_WIDTH / 2 - 200, -100, 400),
      create_platform(DISPLAY_WIDTH - 400, 150, 400),
      create_platform(0, 400, 300),
      create_platform(0, 650, DISPLAY_WIDTH),
  };
  PlatformHandler platform_handler = create_platform_handler();

  Uint8 game_state = STATE_INPUT_AWAIT;

  Uint16 score = 0;
  Text score_text = create_text(0, 0, "NDUAWBDWYUIOA", (SDL_Color){255, 255, 255, 255}, 48, renderer);

  Uint8 quit = 0;
  SDL_Event event = {0};

  Uint16 desired_frame_delta = 1000.0 / FPS;

  // Main game loop
  while (!quit) {
    // Time of beginning of the frame
    Uint32 frame_start_time = SDL_GetTicks();

    // Handle events
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      // ESC key
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
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
    const Uint8 *kb = SDL_GetKeyboardState(NULL);

    // Draw background
    scc(SDL_SetRenderDrawColor(renderer, BG_COLOR_RED, BG_COLOR_BLUE,
                               BG_COLOR_GREEN, BG_COLOR_ALPHA));
    scc(SDL_RenderClear(renderer));

    if (game_state == STATE_INPUT_AWAIT) {
      if (kb[SDL_SCANCODE_SPACE]) {
        game_state = STATE_RUNNING;
      }
    }

    else if (game_state == STATE_RUNNING) {
      // Update hero
      agent_move(&hero, kb[SDL_SCANCODE_D] + -kb[SDL_SCANCODE_A]);
      if (kb[SDL_SCANCODE_SPACE]) {
        agent_jump(&hero);
      }
      agent_update(&hero);
      agent_collide_border(&hero);
      if (hero.rect.y > DISPLAY_HEIGHT) {
        game_state = STATE_DEATH_ANIMATION;
        agent_die(&hero);
      }

      // Update platforms
      for (int i = 0; i < NUMBER_OF_PLATFORMS; i++) {
        if (platforms[i].rect.y >= DISPLAY_HEIGHT) {
          reset_platform(&platforms[i], &platform_handler);

          // Add 1 to score
          score += 1;
        }

        platform_update(&platforms[i]);

        agent_collide_platform(&hero, &platforms[i]);
      }
    }

    else if (game_state == STATE_DEATH_ANIMATION) {
      agent_update(&hero);
      if (hero.rect.y > DISPLAY_HEIGHT + 500) {
        game_state = STATE_INPUT_AWAIT;
        reset_scene(platforms, &hero);
      }
    }

    // Redner platforms
    for (int i = 0; i < NUMBER_OF_PLATFORMS; i++) {
      platform_render(&platforms[i], renderer);
    }

    // Redner agents
    agent_render(&hero, renderer);

    // Update and draw fire
    fire_draw(&fire, renderer);
    fire_update(&fire);

    // Render score
    render_text(&score_text, renderer);

    // Render scene
    SDL_RenderPresent(renderer);

    // Cap frame rate
    Uint32 frame_time_delta = SDL_GetTicks() - frame_start_time;
    if (frame_time_delta < desired_frame_delta) {
      SDL_Delay(desired_frame_delta - frame_time_delta);
    }
  }

  free_text(&score_text);
  SDL_Quit();
  return 0;
}
