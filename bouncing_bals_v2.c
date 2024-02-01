#include "raylib.h"
#include <stdio.h>
#include <math.h>

double distance(Vector2 a, Vector2 b);

typedef struct Particle{
	Vector2 pos;
	Vector2 vel;
} Particle;

int main() {
	const int screenWidth = 1200;	
	const int screenHeight = 800;
	const int max_num_of_balls = 50;

	const int radius = 50;

	int num_of_balls = 0;

	Particle balls[max_num_of_balls];
	
	InitWindow(screenWidth, screenHeight, "raylib - multiple bouncing balls v2");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_SPACE)) {
			Vector2 ball_pos = {(float)screenWidth/2, (float)screenHeight/2};
			Vector2 ball_vel = {5.0f, 4.0f};
			balls[num_of_balls].pos = ball_pos;
			balls[num_of_balls].vel = ball_vel;

			num_of_balls += 1;
		}

		BeginDrawing();

		ClearBackground(RAYWHITE);

		for (int i=0; i<num_of_balls; i++) {
			balls[i].pos.x += balls[i].vel.x;
			balls[i].pos.y += balls[i].vel.y;
			
			// Colission Detection

			// Between ball and wall
			if ((balls[i].pos.x >= (GetScreenWidth() - radius)) || (balls[i].pos.x <= radius)) {
				balls[i].vel.x *= -1.0f;
			}
			if ((balls[i].pos.y >= (GetScreenHeight() - radius)) || (balls[i].pos.y <= radius)) {
				balls[i].vel.y *= -1.0f;
			}

			// Between balls
			for (int j=0; j<i; j++) {
				double dist = distance(balls[j].pos, balls[i].pos);

				if (dist < radius*2) {
					// primeiro caso, x's iguais e y's diferentes
					if (balls[i].vel.x*balls[j].vel.x > 0) {
						balls[i].vel.y *= -1.0f;
						balls[j].vel.y *= -1.0f;
					} else if (balls[i].vel.y*balls[j].vel.y > 0) {
						balls[i].vel.x *= -1.0f;
						balls[j].vel.x *= -1.0f;
					} else {
						balls[i].vel.x *= -1.0f;
						balls[j].vel.x *= -1.0f;
						balls[i].vel.y *= -1.0f;
						balls[j].vel.y *= -1.0f;
					}
				}
			}

			DrawCircleV(balls[i].pos, radius, MAROON);
		}
		
		EndDrawing();

	}

	CloseWindow();

	return 0;

}

double distance(Vector2 a, Vector2 b) {
	return sqrt((pow((a.x - b.x), 2)) + (pow((a.y - b.y), 2))); 
}
