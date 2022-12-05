#ifndef AGENT_H
#define AGENT_H

// States
#define AGENT_STATE_ALIVE 0
#define AGENT_STATE_DEAD 1

#define AGENT_GROUNDED 0
#define AGENT_NOT_GROUNDED 1

// Agents parameters
#define AGENT_WIDTH 50
#define AGENT_HEIGHT 50
#define AGENT_MOVEMENT_ACCELERATION 10
#define AGENT_MAX_SPEED 30
#define AGENT_DRAG_FORCE 1.5f

#define AGENT_GRAVITY_FORCE 4
#define AGENT_JUMP_FORCE 50

typedef struct {
  SDL_Rect rect;
  Vector2 prev_pos;
  SDL_Color color;
  Uint8 state;
  Vector2 velocity;
  Vector2 acceleration;
  float movement_acceleration;
  float max_speed;
  float drag_force;
  Uint8 grounded;
} Agent;

Agent create_agent(int x, int y);
void agent_render(Agent *agent, SDL_Renderer *renderer);
void agent_move(Agent *agent, Sint8 direction);
void agent_update(Agent *agent);
void agent_collide_platform(Agent *agent, Platform *platform);
void agent_collide_border(Agent *agent);
void agent_apply_gravity(Agent *agent);
void agent_jump(Agent *agent);
void agent_die(Agent *agent);

#endif // AGENT_H
