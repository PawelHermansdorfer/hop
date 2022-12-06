#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include <main_agent.h>
#include <main_base.h>
#include <main_platform.h>
#include <main_vectors.h>

// Returns new agent
Agent create_agent(int x, int y) {
  return (Agent){
      .rect = {(int)x, (int)y, AGENT_WIDTH, AGENT_HEIGHT},
      .prev_pos = CreateVector2(0, 0),
      .color = (SDL_Color){AGENT_COLOR_RED, AGENT_COLOR_GREEN, AGENT_COLOR_BLUE,
                           AGENT_COLOR_ALPHA},
      .state = AGENT_STATE_ALIVE,
      .velocity = CreateVector2(0, 0),
      .acceleration = CreateVector2(0, 0),
      .movement_acceleration = AGENT_MOVEMENT_ACCELERATION,
      .max_speed = AGENT_MAX_SPEED,
      .drag_force = AGENT_DRAG_FORCE,
      .grounded = AGENT_NOT_GROUNDED,
  };
}

// Renders agent
void agent_render(Agent *agent, SDL_Renderer *renderer) {
  scc(SDL_SetRenderDrawColor(renderer, agent->color.r, agent->color.g,
                             agent->color.b, agent->color.a));
  scc(SDL_RenderFillRect(renderer, &agent->rect));
}

// Updates agent
void agent_update(Agent *agent) {
  // Apply gravity
  agent_apply_gravity(agent);

  // Apply drag force on x axes
  agent->velocity.x = agent->velocity.x / agent->drag_force;

  // Add acceleration to velocity and reset acceleration
  agent->velocity = Vector2Add(agent->velocity, agent->acceleration);
  agent->acceleration = CreateVector2(0, 0);

  // Limit agent movement_speed
  if (agent->velocity.x > agent->max_speed) {
    agent->velocity.x = agent->max_speed;
  } else if (agent->velocity.x < -agent->max_speed) {
    agent->velocity.x = -agent->max_speed;
  }

  // Update previous position
  agent->prev_pos.x = agent->rect.x;
  agent->prev_pos.y = agent->rect.y;

  // set agent position
  agent->rect.x += (int)(agent->velocity.x);
  agent->rect.y += (int)(agent->velocity.y);
}

// Handles collision between agents and platforms
void agent_collide_platform(Agent *agent, Platform *platform) {
  if (agent->rect.y + agent->rect.h >
          platform->rect.y // Bottom of agent lower than top of platform
      && agent->rect.y <
             platform->rect.y +
                 platform->rect.h // Top of agent higher than bottom of platform
      && agent->rect.x + agent->rect.w >
             platform->rect
                 .x // Right side fo agent further than left side of platform
      && agent->rect.x <
             platform->rect.x + platform->rect.w) // Left side of agent closer
                                                  // than right side of platform
  {
    if (agent->prev_pos.x + agent->rect.w <=
        platform->rect.x) // Hit platform from left side
    {
      agent->rect.x = platform->rect.x - agent->rect.w;
      agent->velocity.x = 0;
      agent->acceleration.x = 0;
    }

    else if (agent->prev_pos.x >=
             platform->rect.x +
                 platform->rect.w) // Hit platform from right side
    {
      agent->rect.x = platform->rect.x + platform->rect.w;
      agent->velocity.x = 0;
      agent->acceleration.x = 0;
    }

    else if (agent->prev_pos.y >=
             platform->rect.y + platform->rect.h -
                 platform->velocity) // Hit platform from below
    {
      agent->rect.y = platform->rect.y + platform->rect.h + platform->velocity;
      agent->velocity.y = 0;
      agent->acceleration.y = 0;
    } else if (agent->prev_pos.y + agent->rect.h <=
               platform->rect.y) // Hit platform from above
    {
      agent->grounded = AGENT_GROUNDED;
      agent->rect.y = platform->rect.y - agent->rect.h;
      agent->velocity.y = 0;
      agent->acceleration.y = 0;
    }
  }
}

// Constrains agent in display area
void agent_collide_border(Agent *agent) {
  // Left side
  if (agent->rect.x < 0) {
    agent->rect.x = 0;
    agent->velocity.x = 0;
    agent->velocity.x = 0;
  } else if (agent->rect.x + agent->rect.w > DISPLAY_WIDTH) {
    agent->rect.x = DISPLAY_WIDTH - agent->rect.w;
    agent->velocity.x = 0;
    agent->velocity.x = 0;
  }
}

// Applies gravity on agent
void agent_apply_gravity(Agent *agent) {
  agent->acceleration.y += AGENT_GRAVITY_FORCE;
}

// 1 -> right || 1 -> left
void agent_move(Agent *agent, Sint8 direction) {
  agent->acceleration.x = direction * agent->movement_acceleration;
}

// Makes agent jump
void agent_jump(Agent *agent) {
  if (agent->grounded == AGENT_GROUNDED) {
    agent->acceleration.y -= AGENT_JUMP_FORCE;
    agent->velocity.y = 0;
    agent->grounded = AGENT_NOT_GROUNDED;
  }
}

// Death animation
void agent_die(Agent *agent) {
  agent->acceleration.y -= AGENT_JUMP_FORCE * 1.5;
  agent->velocity.y = 0;
}
