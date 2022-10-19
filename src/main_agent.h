#ifndef AGENT_H
#define AGENT_H

// Agents parameters
#define AGENT_WIDTH 50
#define AGENT_HEIGHT 50
#define AGENT_MOVEMENT_ACCELERATION 10
#define AGENT_MAX_SPEED 30
#define AGENT_DRAG_FORCE 1.5f

#define AGENT_GRAVITY_FORCE 4
#define AGENT_JUMP_FORCE 50

typedef struct
{
 SDL_Rect rect;
 SDL_Color color;
 Vector2 velocity;
 Vector2 acceleration;
 float movement_acceleration;
 float max_speed;
 float drag_force;
 Uint8 grounded;
}
Agent;

Agent create_agent(float x, float y, Uint8 w, Uint8 h, SDL_Color color);
void agent_render(Agent *agent, SDL_Renderer *renderer);
void agent_move(Agent *agent, Sint8 direction);
void agent_update(Agent *agent);
void agent_collide_platform(Agent *agent, Platform *platform);
void agent_apply_gravity(Agent *agent);
void agent_jump(Agent *agent);

#endif // AGENT_H
