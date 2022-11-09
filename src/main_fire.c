#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <main_base.h>
#include <main_vectors.h>
#include <main_fire.h>

// TODO(Aa_Pawelek): Implement algorithm to lerp between colors with  predefined step size
const int fire_palette[FIRE_PALETTE_SIZE][4] = {{0, 0, 0, 255}, {14, 0, 0, 255}, {43, 0, 0, 255}, {71, 0, 0, 255}, {99, 0, 0, 255}, {128, 0, 0, 255}, {156, 0, 0, 255}, {184, 0, 0, 255}, {213, 0, 0, 255}, {241, 0, 0, 255}, {255, 9, 0, 255}, {255, 28, 0, 255}, {255, 46, 0, 255}, {255, 64, 0, 255}, {255, 83, 0, 255}, {255, 101, 0, 255}, {255, 119, 0, 255}, {255, 138, 0, 255}, {255, 156, 0, 255}, {255, 170, 0, 255}, {255, 180, 0, 255}, {255, 190, 0, 255}, {255, 200, 0, 255}, {255, 210, 0, 255}, {255, 220, 0, 255}, {255, 230, 0, 255}, {255, 240, 0, 255}, {255, 250, 0, 255}, {255, 255, 14, 255}, {255, 255, 43, 255}, {255, 255, 71, 255}, {255, 255, 99, 255}, {255, 255, 128, 255}, {255, 255, 156, 255}, {255, 255, 184, 255}, {255, 255, 213, 255}, {255, 255, 241, 255}};

Fire create_fire(void)
{
 Fire fire = {.fire_partices = {{}}};

 for (int i = i; i < FIRE_N_ROWS; i++) // First collumn always must be white
 {
  for (int j = 0; j < FIRE_N_COLS; j++)
  {
   if (i == FIRE_N_ROWS - 1) {
    fire.fire_partices[i][j] = FIRE_PALETTE_SIZE - 1;
   }
   else {
    fire.fire_partices[i][j] = 0; 
   }
  }
 }

 return fire;
}

void fire_draw(Fire *fire, SDL_Renderer *renderer)
{
 int particle_offset = DISPLAY_HEIGHT - (FIRE_N_ROWS * FIRE_PARTICLE_SIZE);

 for (int i = 0; i < FIRE_N_ROWS; i++)
 {
  for (int j = 0; j < FIRE_N_COLS; j++)
  {
  int color_index = fire->fire_partices[i][j];
  if (color_index != 0)
  {
   scc(SDL_SetRenderDrawColor(renderer, fire_palette[color_index][0], fire_palette[color_index][1], fire_palette[color_index][2], fire_palette[color_index][3]));
   SDL_Rect rect = {j * FIRE_PARTICLE_SIZE, particle_offset + i * FIRE_PARTICLE_SIZE, FIRE_PARTICLE_SIZE, FIRE_PARTICLE_SIZE};
   scc(SDL_RenderFillRect(renderer, &rect));
  }
  }
 }
}


void fire_update(Fire *fire)
{
 for (int i = 1; i < FIRE_N_ROWS; i++)
 {
  for (int j = 0; j < FIRE_N_COLS; j++)
  {
   int color_index = fire->fire_partices[i][j];
   if (color_index != 0)
   {
    int rnd = rand() % 4;
    fire->fire_partices[i - 1][j - rnd + 1] = color_index - (rnd % 2);
   }
   else
   {
    fire->fire_partices[i-1][j] = 0;
   }
  }
 }
}
