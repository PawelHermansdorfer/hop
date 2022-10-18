#ifndef AGENT_H
#define AGENT_H

#define AGENT_MOVEMENT_ACCELERATION 10
#define AGENT_MAX_SPEED 20
#define AGENT_DRAG_FORCE 1.5f
#define AGENT_WIDTH 50
#define AGENT_HEIGHT 50
#define AGENT_GRAVITY_FORCE 10

typedef struct
{
 SDL_Rect rect;
 // SDL_Color color;
 Vector2 speed;
 Vector2 acceleration;
 float movement_acceleration;
 float max_speed;
 float drag_force;
}
Agent;

Agent create_agent(float x, float y);
void agent_move(Agent *agent, Sint8 direction);
void agent_update(Agent *agent);
void agent_apply_gravity(Agent *agent);

#endif // AGENT_H
