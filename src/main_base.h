#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define DISPLAY_WIDTH 560
#define DISPLAY_HEIGHT 900

#define FPS 60

#define NUMBER_OF_PLATFORMS 5

// Background color
#define BG_COLOR_RED 30
#define BG_COLOR_GREEN 30
#define BG_COLOR_BLUE 30
#define BG_COLOR_ALPHA 255

// Ground settings
#define PLATFORM_COLOR_RED 255
#define PLATFORM_COLOR_GREEN 192
#define PLATFORM_COLOR_BLUE 203
#define PLATFORM_COLOR_ALPHA 255
#define PLATFORM_HEIGHT 30

// Playable character settings
#define AGENT_COLOR_RED 120
#define AGENT_COLOR_GREEN 220
#define AGENT_COLOR_BLUE 240
#define AGENT_COLOR_ALPHA 255
#define AGENT_WIDTH 50
#define AGENT_HEIGHT 50

// Game states
#define STATE_INPUT_AWAIT 0
#define STATE_RUNNING 1
#define STATE_DEATH_ANIMATION 2

void scc(int error_code);
void *scp(void *ptr);
int map(int value, int A, int B, int a, int b);

#endif // FUNCTIONS_H
