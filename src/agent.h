#ifndef AGENT_H
#define AGENT_H

#define AGENT_MOVEMENT_SPEED 10
#define AGENT_MAX_SPEED 20
#define AGENT_DRAG_FORCE 1.5f
#define AGENT_WIDTH 50
#define AGENT_HEIGHT 50

typedef struct
{
 SDL_Rect rect;
 Vector2 speed;
 float movement_speed;
 float max_speed;
 float drag_force;
 Vector2 acceleration;
}
Agent;

Agent create_agent(Uint32 x, Uint32 y);
void move_agent(Agent *agent, Sint8 direction);
void update_agent(Agent *agent);
void apply_gravity(Agent *agent);

#endif // AGENT_H
