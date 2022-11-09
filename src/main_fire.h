#ifndef FIRE_H
#define FIRE_H

// #define FIRE_DENSITY 10
#define FIRE_PARTICLE_SIZE 4
#define FIRE_PALETTE_SIZE 37

#define FIRE_N_COLS DISPLAY_WIDTH / FIRE_PARTICLE_SIZE
#define FIRE_N_ROWS FIRE_PALETTE_SIZE * 10

typedef struct
{
 int fire_partices[FIRE_N_ROWS][FIRE_N_COLS];
}
Fire;

Fire create_fire(void);
void fire_draw(Fire *fire, SDL_Renderer *renderer);
void fire_update(Fire *fire);

#endif // FIRE_H
