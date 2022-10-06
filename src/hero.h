#ifndef HERO_H
#define HERO_H


typedef struct {
 SDL_Rect rect;
 Vector2 speed;
 float max_speed;
 float drag_force;
 Vector2 acceleration;
 float movement_speed;
}
Character;

Character CreateHero(void);
void MoveCharacter(Character *character, Sint8 direction);
void update_character(Character *character);
void ApplyGravity(Character *character);

#endif