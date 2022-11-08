#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define DISPLAY_WIDTH 550
#define DISPLAY_HEIGHT 900

#define NUMBER_OF_PLATFORMS 2

// Background color
#define BG_COLOR_RED 30
#define BG_COLOR_GREEN 30
#define BG_COLOR_BLUE 30
#define BG_COLOR_ALPHA 0

// Lava settings
#define LAVA_COLOR_RED 207
#define LAVA_COLOR_GREEN 96
#define LAVA_COLOR_BLUE 16
#define LAVA_COLOR_ALPHA 0
#define LAVA_WIDTH DISPLAY_WIDTH
#define LAVA_HEIGHT 50
#define LAVA_POS_X 0
#define LAVA_POS_Y DISPLAY_HEIGHT - LAVA_HEIGHT

// Ground settings
#define PLATFORM_COLOR_RED 255
#define PLATFORM_COLOR_GREEN 192
#define PLATFORM_COLOR_BLUE 203
#define PLATFORM_COLOR_ALPHA 0
#define PLATFORM_HEIGHT 30

// Playable character settings
#define AGENT_COLOR_RED 120
#define AGENT_COLOR_GREEN 220
#define AGENT_COLOR_BLUE 240
#define AGENT_COLOR_ALPHA 0
#define AGENT_WIDTH 50
#define AGENT_HEIGHT 50

void scc(int error_code);
void *scp(void *ptr);

#endif // FUNCTIONS_H
