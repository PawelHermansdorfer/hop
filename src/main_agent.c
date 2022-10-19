#include <SDL2/SDL.h>
#include <stdio.h>

#include <main_base.h>
#include <main_vectors.h>
#include <main_platform.h>
#include <main_agent.h>

// Returns new agent
Agent create_agent(float x, float y, Uint8 w, Uint8 h, SDL_Color color)
{
 return (Agent) {
  .rect = {(int)x, (int)y, (int)w, (int)h},
  .color = color,
  .velocity = CreateVector2(0, 0),
  .acceleration = CreateVector2(0, 0),
  .movement_acceleration = AGENT_MOVEMENT_ACCELERATION,
  .max_speed = AGENT_MAX_SPEED,
  .drag_force = AGENT_DRAG_FORCE,
  .grounded = 0,
 };
}

// Renders agent
void agent_render(Agent *agent, SDL_Renderer *renderer)
{
  scc(SDL_SetRenderDrawColor(
   renderer,
   agent->color.r,
   agent->color.g,
   agent->color.b,
   agent->color.a
  ));
  scc(SDL_RenderFillRect(renderer, &agent->rect));
}

// Updates agent
void agent_update(Agent *agent)
{
 // Apply gravity
 agent_apply_gravity(agent);

 // Apply drag force on x axes
 agent->velocity.x = agent->velocity.x / agent->drag_force;

 // Add acceleration to velocity and reset acceleration
 agent->velocity = Vector2Add(agent->velocity, agent->acceleration);
 agent->acceleration = CreateVector2(0, 0);

 // Limit agent movement_speed
 if (agent->velocity.x > agent->max_speed)
 {
  agent->velocity.x = agent->max_speed;
 }
 else if (agent->velocity.x < -agent->max_speed)
 {
  agent->velocity.x = -agent->max_speed;
 }

 // set agent position
 printf("%f\n", agent->velocity.x);
 agent->rect.x += round(agent->velocity.x);
 agent->rect.y += round(agent->velocity.y);

}

// Handles collision between agents and platforms
void agent_collide_platform(Agent *agent, Platform *platform)
{
 if (agent->rect.y + agent->rect.h > platform->rect.y)
 {
  agent->rect.y = platform->rect.y - agent->rect.h;
  agent->grounded = 1;
  agent->velocity.y = 0;
 }
 else if (agent->grounded)
 {
  agent->grounded = 0;
 }
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

// Makes agent jump
void agent_jump(Agent *agent)
{
 if (agent->grounded)
 {
  agent->acceleration.y -= AGENT_JUMP_FORCE;
 }
}