#include <main_vectors.h>

// Returns vector2
Vector2 CreateVector2(float x, float y) { return (Vector2){.x = x, .y = y}; }


// Returns sum of two vectors2
Vector2 Vector2Add(Vector2 vec_a, Vector2 vec_b) {
  return CreateVector2(vec_a.x + vec_b.x, vec_a.y + vec_b.y);
}

// Returns result of subtracting two vectors2
Vector2 Vector2Sub(Vector2 vec_a, Vector2 vec_b) {
  return CreateVector2(vec_a.x - vec_b.x, vec_a.y - vec_b.y);
}

// Returns result of dividing two vectors2
Vector2 Vector2Div(Vector2 vec_a, Vector2 vec_b) {
  return CreateVector2(vec_a.x / vec_b.x, vec_a.y / vec_b.y);
}

// Returns result of the multiplying two vectors2
Vector2 Vector2Mult(Vector2 vec_a, Vector2 vec_b) {
  return CreateVector2(vec_a.x * vec_b.x, vec_a.y * vec_b.y);
}

// Returns result of dividing vector2 by float
Vector2 Vector2DivF(Vector2 vec, float n) {
  return CreateVector2(vec.x / n, vec.y / n);
}
