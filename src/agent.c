#include <SDL2/SDL.h>
#include <stdio.h>

#include <vectors.h>
#include <agent.h>

// Returns agent
Agent create_agent(Uint32 x, Uint32 y) {
 return (Agent) {.rect = {x, y, AGENT_WIDTH, AGENT_HEIGHT},
                     .speed = CreateVector2(0, 0),
                     .max_speed = AGENT_MAX_SPEED,
                     .drag_force = AGENT_DRAG_FORCE,
                     .acceleration = CreateVector2(0, 0),
                     .movement_speed = AGENT_MOVEMENT_SPEED,
                     };
}

// Updates position of agent
void update_agent(Agent *agent)
{
 // Add acceleration to speed
 agent->speed = Vector2Add(agent->speed, agent->acceleration);

 // Reset acceleration
 agent->acceleration = CreateVector2(0, 0);

 // Limit agent speed
 if (agent->speed.x > agent->max_speed)
 {
  agent->speed.x = agent->max_speed;
 }
 else if (agent->speed.x < -agent->max_speed)
 {
  agent->speed.x = -agent->max_speed;
 }

 // Apply drag force
 agent->speed = Vector2DivF(agent->speed, agent->drag_force);

 // set agent position
 agent->rect.x += round(agent->speed.x);
 agent->rect.y += round(agent->speed.y);

}

// Applies gravity on agent
void apply_gravity(Agent *agent)
{
 // TODO(Aa_Pawelek): Gravity
}

// 1 -> right || 1 -> left
void move_agent(Agent *agent, Sint8 direction)
{
 agent->acceleration.x = direction * agent->movement_speed;
}
