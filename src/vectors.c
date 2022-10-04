#include <vectors.h>


Vector2 CreateVector2(float x, float y)
{
 return (Vector2) {.x = x, .y = y};
}

double Vector2GetMagnitude(Vector2 vec)
{
 return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

Vector2 Vector2Normalized(Vector2 vec)
{
 double vec_magintude = Vector2GetMagnitude(vec);
 return CreateVector2(vec.x / vec_magintude, vec.y / vec_magintude);
}

Vector2 Vector2Add(Vector2 vec_a, Vector2 vec_b)
{
 return CreateVector2(vec_a.x + vec_b.x, vec_a.y + vec_b.y);
}

Vector2 Vector2Sub(Vector2 vec_a, Vector2 vec_b)
{
 return CreateVector2(vec_a.x - vec_b.x, vec_a.y - vec_b.y);
}

Vector2 Vector2Div(Vector2 vec_a, Vector2 vec_b)
{
 return CreateVector2(vec_a.x / vec_b.x, vec_a.y / vec_b.y);
}

Vector2 Vector2Mult(Vector2 vec_a, Vector2 vec_b)
{
 return CreateVector2(vec_a.x * vec_b.x, vec_a.y * vec_b.y);
}