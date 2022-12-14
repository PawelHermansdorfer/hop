#ifndef FIRE_H
#define FIRE_H

#include <SDL.h>
#include <main_base.h>

// #define FIRE_DENSITY 10
#define FIRE_PARTICLE_SIZE 4
#define FIRE_PALETTE_SIZE 17

#define N_FIRE_SECTIONS 2
#define FIRE_N_COLS (DISPLAY_WIDTH / FIRE_PARTICLE_SIZE) / N_FIRE_SECTIONS
#define FIRE_N_ROWS FIRE_PALETTE_SIZE * 3

typedef struct {
  int fire_partices[FIRE_N_ROWS][FIRE_N_COLS];
} Fire;

Fire create_fire(void);
void fire_draw(Fire *fire, SDL_Renderer *renderer);
void fire_update(Fire *fire);

#endif // FIRE_H
