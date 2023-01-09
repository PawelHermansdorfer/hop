#ifndef VECTORS_H
#define VECTORS_H

typedef struct {
  float x, y;
} Vector2;

Vector2 CreateVector2(float x, float y);
Vector2 Vector2Add(Vector2 vec_a, Vector2 vec_b);
Vector2 Vector2Sub(Vector2 vec_a, Vector2 vec_b);
Vector2 Vector2Div(Vector2 vec_a, Vector2 vec_b);
Vector2 Vector2Mult(Vector2 vec_a, Vector2 vec_b);
Vector2 Vector2DivF(Vector2 vec, float n);

#endif // VECTORS_H
