#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "raycast.c"
#include "points.c"

#define height 1024
#define width 720
#define pointsA 7

int main() {

    srand(time(NULL));

    Vector2 points_array[pointsA];

    bool is_not_unique = true;

    for (int t = 0; t < pointsA; t++) {

        is_not_unique = true;

        while (is_not_unique) {

            int random_x = rand() % (height);
            int random_y = rand() % (width);

            for (int i = 0; i < pointsA; i++) {

                if (points_array[i].x == random_x && points_array[i].y == random_y) {
                    continue;
                } else {
                    points_array[t] = (Vector2){ .x = random_x, .y = random_y };
                    is_not_unique = false;
                    break;
                }

            }

        }

    }

    SetTraceLogLevel(LOG_WARNING);
    SetTargetFPS(30);
    InitWindow(height, width, "HELLO");

    int guardX, guardY;
    bool isLocationSelected = false;

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);

        Vector2 points[3] = {
            (Vector2){.x = 100, .y = 100},
            (Vector2){.x = 500, .y = 300},
            (Vector2){.x = 200, .y = 500},
        };

        for (int t = 0; t < pointsA; t++) {
            DrawLine(points_array[t].x, points_array[t].y, points_array[t+1].x, points_array[t+1].y, RED);
        }

        EndDrawing();

        for (int i = 0; i < 3; i++)
        {
            if (i == 2)
            {
                DrawLine(points[i].x, points[i].y, points[0].x, points[0].y, GREEN);
            }
            else
            {
                DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, GREEN);
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true)
        {
            guardX = GetMouseX();
            guardY = GetMouseY();
            isLocationSelected = true;
        }

        if (isLocationSelected == true)
        {
            raycastAtPos((Vector3){.x = guardX, .y = guardY, .z = 0}, points);
        }

        // printf("END FRAME------------------------------------\n");
        EndDrawing();
    }

    return 0;
}
