#include <math.h>
#include <stdio.h>
#include <SDL.h>
#if WINDOWS
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL_ttf.h>
#endif

#include <main_agent.h>
#include <main_base.h>
#include <main_fire.h>
#include <main_platform.h>
#include <main_text.h>
#include <main_vectors.h>

void reset_scene(Platform platforms[NUMBER_OF_PLATFORMS], Agent *hero) {
  platforms[0] = create_platform(DISPLAY_WIDTH / 2 - 150, -350, 300);
  platforms[1] = create_platform(DISPLAY_WIDTH / 2 - 200, -100, 400);
  platforms[2] = create_platform(DISPLAY_WIDTH - 400, 150, 400);
  platforms[3] = create_platform(0, 400, 300);
  platforms[4] = create_platform(0, 650, DISPLAY_WIDTH);

  *hero = create_agent(DISPLAY_WIDTH / 2 - AGENT_WIDTH / 2, 650 - AGENT_HEIGHT);
}

int read_best_score(void) {
  FILE *file;
  int score = 0;
  /* fopen_s(&file, "best_score.dat", "r"); */
  file = fopen("best_score.dat", "r");
  if (file) {
    fscanf(file, "%d", &score);
    fclose(file);
  }
  return score;
}

void write_best_score(const char *score_str)
{
  FILE *file;
  /* fopen_s(&file, "best_score.dat", "w"); */
  file = fopen("best_score.dat", "w");
  fputs(score_str, file);
  fclose(file);
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
  char score_str[64];
  /* sprintf_s(score_str, 64, "score: %d", score); */
  sprintf(score_str, "score: %d", score);

  
  Uint16 best_score = read_best_score();
  char best_score_str[64];
  sprintf(best_score_str, "best score: %d", best_score);

  Uint16 current_score = 0;
  char current_score_str[64];
  sprintf(current_score_str, "%d", current_score);

  Text score_text = create_text(-1, 65, score_str,
                                (SDL_Color){255, 255, 255, 255}, 64, renderer);

  Text best_score_text = create_text(
      -1, 120, best_score_str, (SDL_Color){255, 255, 255, 255}, 32, renderer);

  Text press_space_text = create_text(
      -1, DISPLAY_HEIGHT-200, "press space to start", (SDL_Color){255, 255, 255, 255}, 42, renderer);

  Text  current_score_text = create_text(
      -1, DISPLAY_HEIGHT/6, current_score_str, (SDL_Color){255, 255, 255, 255}, 96, renderer);

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

    // Redner platforms
    for (int i = 0; i < NUMBER_OF_PLATFORMS; i++) {
      platform_render(&platforms[i], renderer);
    }

    // Redner agents
    agent_render(&hero, renderer);

    // Update and draw fire
    fire_draw(&fire, renderer);
    fire_update(&fire);

    if (game_state == STATE_INPUT_AWAIT) {
      // Render score
      render_text(&score_text, renderer);
      render_text(&best_score_text, renderer);
      render_text(&press_space_text, renderer);

      if (kb[SDL_SCANCODE_SPACE]) {
        game_state = STATE_RUNNING;
      }
    }

    if (game_state == STATE_RUNNING) {
      // Render score
      render_text(&current_score_text, renderer);

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
          sprintf(current_score_str, "%d", score);
          update_text(&current_score_text, current_score_str, renderer);
        }

        platform_update(&platforms[i]);

        agent_collide_platform(&hero, &platforms[i]);
      }
    }

    if (game_state == STATE_DEATH_ANIMATION) {
      // Render score
      render_text(&current_score_text, renderer);

      agent_update(&hero);
      if (hero.rect.y > DISPLAY_HEIGHT + 500) {
        game_state = STATE_INPUT_AWAIT;
        reset_scene(platforms, &hero);


        sprintf(score_str, "Score: %d", score);
        update_text(&score_text, score_str, renderer);
        if (score > best_score) {
          best_score = score;
        sprintf(best_score_str, "best score: %d", best_score);
        update_text(&best_score_text, best_score_str, renderer);
        }

        score = 0;
        current_score = 0;
      }
    }

    // Render scene
    SDL_RenderPresent(renderer);

    // Cap frame rate
    Uint32 frame_time_delta = SDL_GetTicks() - frame_start_time;
    if (frame_time_delta < desired_frame_delta) {
      SDL_Delay(desired_frame_delta - frame_time_delta);
    }
  }
  sprintf(best_score_str, "%d", best_score);
  write_best_score(best_score_str);

  free_text(&score_text);
  free_text(&best_score_text);
  free_text(&current_score_text);
  free_text(&press_space_text);
  SDL_Quit();
  return 0;
}
