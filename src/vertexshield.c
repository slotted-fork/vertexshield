#include <stdlib.h>

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

int main(void)
{
	const int screenWidth = 1050;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Vertex Shield");

	int screenUpperLimit = 40;

	SetTargetFPS(120);

	struct Fragment fragments[] = {
		{
			.kind = FK_BASIC,
			.rect = {42.0f, GetScreenHeight() / 2.0f - 50.0f, 10, 10},
			.dx = 1.42f,
			.dy = 0.69f
		},
		{
			.kind = FK_MODERN,
			.rect = {69.0f, GetScreenHeight() / 2.0f + 50.0f, 10, 10},
			.dx = 1.69f,
			.dy = 0.42f
		},
	};

	struct Construct constructs[] = {};
	(void)constructs;

	while (!WindowShouldClose()) {
		for (size_t i = 0; i < sizeof fragments / sizeof fragments[0]; ++i) {
			fragments[i].rect.x += fragments[i].dx;
			if (((fragments[i].rect.x + fragments[i].rect.width) >=
			     GetScreenWidth()) ||
			    (fragments[i].rect.x <= 0)) {
				fragments[i].dx *= -1;
			}
			fragments[i].rect.y += fragments[i].dy;
			if (((fragments[i].rect.y + fragments[i].rect.width) >=
			     GetScreenHeight()) ||
			    (fragments[i].rect.y <= screenUpperLimit)) {
				fragments[i].dy *= -1;
			}
		}

		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawRectangle(0, 0, screenWidth, screenUpperLimit, WHITE);
		DrawFPS(10, 10);

		for (size_t i = 0; i < sizeof fragments / sizeof fragments[0]; ++i) {
			switch(fragments[i].kind) {
                        case FK_BASIC: {
				DrawRectangleRec(fragments[i].rect, ORANGE);
				break;
                        }
                        case FK_MODERN: {
				DrawRectangleRec(fragments[i].rect, GREEN);
				break;
                        }
                        default:
				DrawRectangleRec(fragments[i].rect, BLACK);
                        }
                }

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
