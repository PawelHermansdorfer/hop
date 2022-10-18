#include <SDL2/SDL.h>
#include <stdio.h>

#include <agent.h>
#include <vectors.h>
#include <platform.h>

// Returns new agent
Agent create_agent(Sint32 x, Sint32 y)
{
 return (Agent) {
  .rect = {x, y, AGENT_WIDTH, AGENT_HEIGHT},
  // .color = {120, 220, 240, 0},
  .speed = CreateVector2(0, 0),
  .acceleration = CreateVector2(0, 0),
  .movement_acceleration = AGENT_MOVEMENT_ACCELERATION,
  .max_speed = AGENT_MAX_SPEED,
  .drag_force = AGENT_DRAG_FORCE,
 };
}

// Updates agent
void agent_update(Agent *agent)
{
 // Apply gravity
 agent_apply_gravity(agent);

 // Add acceleration to speed and reset acceleration
 agent->speed = Vector2Add(agent->speed, agent->acceleration);
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

// Handles collision between agents and platforms
void agent_collide(Agent *agent, Platform *platform)
{

}

// Applies gravity on agent
void agent_apply_gravity(Agent *agent)
{
 agent->acceleration.y += AGENT_GRAVITY_FORCE;
}

// 1 -> right || 1 -> left
void agent_move(Agent *agent, Sint8 direction)
{
 agent->acceleration.x = direction * agent->movement_acceleration;
}
