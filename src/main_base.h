#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600


// Background color
#define BG_COLOR_RED 30
#define BG_COLOR_GREEN 30
#define BG_COLOR_BLUE 30
#define BG_COLOR_ALPHA 0

// Ground settings
#define GROUND_COLOR_RED 255
#define GROUND_COLOR_GREEN 192
#define GROUND_COLOR_BLUE 203
#define GROUND_COLOR_ALPHA 0
#define GROUND_WIDTH 40

// Playable character settings
#define HERO_COLOR_RED 120
#define HERO_COLOR_GREEN 220
#define HERO_COLOR_BLUE 240
#define HERO_COLOR_ALPHA 0
#define HERO_WIDTH 50
#define HERO_HEIGHT 50

void scc(int error_code);
void *scp(void *ptr);

#endif // FUNCTIONS_H
