#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"

// The Corruption is made out of Fragments
typedef enum {
     FK_BASIC,
     FK_MODERN,

     FK_COUNT,
} Fragment_Kind;

struct Fragment {
     Fragment_Kind kind;
     Rectangle rect;
     float dx, dy;
     int alive;
};

// The Network is made seom Constructs
typedef enum {
     CK_SHOOTER,

     CK_COUNT,
} Construct_Kind;

struct Construct {
     Construct_Kind kind;
     Rectangle rect;
};

const int SEED = 0;

int main(void)
{
     const int SCREEN_WIDTH = 1050;
     const int SCREEN_HEIGHT = 600;

     /*
       (min_x, min_y)


       (max_x, max_y)
     */

     const float MIN_X = 0, MAX_X = (float)SCREEN_WIDTH, MIN_Y = 40, MAX_Y = (float)SCREEN_HEIGHT;

     SetRandomSeed(SEED);

     const Rectangle start = {.x = 0, .y = MIN_Y, .width = 10, .height = 10 };
     const Rectangle end   = {.x = (MAX_X - 10), .y = (MAX_Y - 10), .width = 10, .height = 10 };

     struct Fragment fragments[1000];
     struct Fragment template = {
	  .kind = FK_BASIC,
	       .rect = {MIN_X, MIN_Y, 10, 10},
	       .dx = 0.5f,
	       .dy = 0.26f,
	       .alive = 0,
     };

     for (int i = 0; i < 1000; i++) {
	  memcpy(&fragments[i], &template, sizeof(struct Fragment));
	  fragments[i].dx += (float)(GetRandomValue(0, 30) - 15) / 100.0f;
	  fragments[i].dy += (float)(GetRandomValue(0, 30) - 15) / 100.0f;
     }

     struct Construct constructs[] = {};

     InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Vertex Shield");


     SetTargetFPS(60);

     char frags_str[100];
     size_t n = 0, f = 0;

     while (!WindowShouldClose()) {
	  ++n;

	  if (!(n % 50) && f < 1000) {
	       fragments[f].alive = 1;
	       printf("frag(%u): x/y/dx/dy/alive: %f/%f/%f/%f/%u\n",
		      f,
		      fragments[f].rect.x, fragments[f].rect.y,
		      fragments[f].dx, fragments[f].dy,
		      fragments[f].alive);
	       ++f;
	  }

          for (size_t i = 0; i < sizeof fragments / sizeof fragments[0]; ++i) {
               struct Fragment *frag = &fragments[i];
	       if (!frag->alive) continue;

	       frag->rect.x += frag->dx;
	       if ((frag->rect.x + frag->rect.width) >= MAX_X
		   || (frag->rect.x <= MIN_X)) {
		    frag->dx *= -1;
	       }
	       frag->rect.y += frag->dy;
	       if ((frag->rect.y + frag->rect.width) >= MAX_Y
		   || (frag->rect.y <= MIN_Y)) {
		    frag->dy *= -1;
	       }
          }

	  {
	       BeginDrawing();

	       ClearBackground(RAYWHITE);
	       DrawRectangle(0, MIN_Y, MAX_X, MAX_Y, LIGHTGRAY);
	       DrawFPS(10, 10);
	       sprintf(frags_str, "Frags: %lu", f);
	       DrawText(frags_str, 200, 10, 20, DARKGREEN);

	       DrawRectangleRec(start, BLACK);
	       DrawRectangleRec(end, RED);

	       for (size_t i = 0; i < sizeof fragments / sizeof fragments[0]; ++i) {
		    struct Fragment *frag = &fragments[i];

		    if (!frag->alive) continue;

		    switch(frag->kind) {
			case FK_BASIC: {
			     DrawRectangleRec(frag->rect, ORANGE);
			} break;

			case FK_MODERN: {
			     DrawRectangleRec(frag->rect, GREEN);
			} break;

			default: {
			     DrawRectangleRec(frag->rect, BLACK);
			}
		    }
	       }

	       EndDrawing();
	  }     }

     CloseWindow();

     return 0;
}
