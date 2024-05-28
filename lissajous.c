#include <stddef.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

// Initial capacity of a dynamic array
#define DA_INIT_CAP 256

// Append an item to a dynamic array
#define da_append(da, item)                                                           \
    do {                                                                              \
        if ((da)->count >= (da)->capacity) {                                          \
            (da)->capacity = (da)->capacity == 0 ? DA_INIT_CAP : (da)->capacity*2;    \
            (da)->items = realloc((da)->items, (da)->capacity*sizeof(*(da)->items));  \
            assert((da)->items != NULL && "The array is to big");                     \
        }                                                                             \
        (da)->items[(da)->count++] = (item);                                          \
    } while (0)


#define COLOR_BACKGROUND CLITERAL(Color){ 28, 28, 28, 255 } 
#define COLOR_MAIN (Color){251,241,199, 255}
#define COLOR_LINES CLITERAL(Color){ 245, 245, 245, 100 }

typedef struct {
    Vector2 *items;
    size_t count;
    size_t capacity;
} Points;


int main(void)
{
  int screenWidth = 800;
  int screenHeight = 800;


  float angle = 0;
  int w = 80;

  int cols = screenWidth/w;
  Points points[100] = {0};
  
  int r = w/2-10; // radius
  
  InitWindow(screenWidth, screenHeight, "Lissajous Curve Table");
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {

    angle += 0.01;

    BeginDrawing();
      ClearBackground(COLOR_BACKGROUND);

      for (size_t i = 1; i < cols; i++) {
        DrawCircleLines(i*w+w/2, w/2, r, COLOR_MAIN);
        DrawCircleLines(w/2, i*w +w/2, r, COLOR_MAIN);

        Vector2 point = {
          r*cosf(angle*i-PI/2),
          r*sinf(angle*i-PI/2)
        };

        DrawCircle(i*w+w/2+point.x, w/2+point.y, 2, COLOR_MAIN);
        DrawLine(i*w+w/2+point.x, w/2+point.y, i*w+w/2+point.x, screenHeight, COLOR_LINES);
        
        DrawCircle(w/2+point.x, i*w + w/2+point.y, 2, COLOR_MAIN);
        DrawLine(w/2+point.x, i*w+w/2+point.y, screenWidth, i*w+w/2+point.y, COLOR_LINES);


        for (size_t j = 1; j < cols; j++) {
          int index = (j-1) + (i-1)*cols;
          Vector2 point = {
            r*cosf(angle*i-PI/2),
            r*sinf(angle*j-PI/2)
          };

          da_append(&points[index], Vector2Add(point, CLITERAL(Vector2){i*w + w/2, j*w + w/2}));
          DrawCircle(i*w+w/2+point.x, j*w + w/2+point.y, 3, COLOR_MAIN);
          DrawSplineLinear(points[index].items, points[index].count, 1.0, COLOR_MAIN);
        }   
      } 

    EndDrawing();

    if (angle > PI*2){
      for (size_t i = 0; i < cols*cols; i++) {
        points[i].count=0;
      }
      angle=0;
    }
  }

  CloseWindow();

  return 0;
}
