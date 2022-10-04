#include <SDL2/SDL.h>

#include <vectors.h>
#include <hero.h>


Character CreateHero(void) {
 Character hero = {.rect = {50, 50, 50, 50},
                   .speed = CreateVector2(0, 0),
                   .max_speed = 10,
                   .acceleration = CreateVector2(0, 0)};
 return hero;
}

void UpdateCharacter(Character *character)
{
 character->speed = Vector2Add(character->speed, character->acceleration);
 character->acceleration = CreateVector2(0, 0);

 character->rect.x += character->speed.x;
 character->rect.y += character->speed.y;
}

void MoveCharacter(Character *character, Sint8 direction)
{
 // 1 -> right || 1 -> left
 character->acceleration.x = direction;
}


void ApplyGravity(Character *character)
{
 character->acceleration.y += 1;
}