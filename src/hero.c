#include <SDL2/SDL.h>
#include <stdio.h>

#include <vectors.h>
#include <hero.h>


Character CreateHero(void) {
 return (Character) {.rect = {50, 50, 50, 50},
                     .speed = CreateVector2(0, 0),
                     .max_speed = 10,
                     .drag_force = 1.5,
                     .acceleration = CreateVector2(0, 0),
                     .movement_speed = 5,
                     };
}


void update_character(Character *character)
{
 character->speed = Vector2Add(character->speed, character->acceleration);
 character->acceleration = CreateVector2(0, 0);

 if (character->speed.x > character->max_speed)
 {
  character->speed.x = character->max_speed;
 }
 else if (character->speed.x < -character->max_speed)
 {
  character->speed.x = -character->max_speed;
 }

 character->speed = Vector2DivF(character->speed, character->drag_force);

 character->rect.x += round(character->speed.x);
 character->rect.y += round(character->speed.y);

}


void ApplyGravity(Character *character)
{
 // TODO(Aa_Pawelek): Gravity
}

// 1 -> right || 1 -> left
void MoveCharacter(Character *character, Sint8 direction)
{
 character->acceleration.x = direction * character->movement_speed;
}
