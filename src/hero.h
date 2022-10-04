#ifndef HERO_H
#define HERO_H


typedef struct {
 SDL_Rect rect;
 Vector2 speed;
 Uint8 max_speed;
 Vector2 acceleration;
} Character;

Character CreateHero(void);
void MoveCharacter(Character *character, Sint8 direction);

#endif