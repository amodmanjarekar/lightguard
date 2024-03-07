#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "./lib/raycast.c"

#define height 1024
#define width 720
#define points 7

typedef struct pass_data {
    Vector2 points_array[7];
}pass_data;

extern void perform(pass_data *d);

int main() {

    srand(time(NULL));

    bool is_not_unique = true;
    Vector2 points_array[points];

    for (int t = 0; t < points; t++) {

        is_not_unique = true;

        while (is_not_unique) {

            int random_x = rand() % (height);
            int random_y = rand() % (width);

            for (int i = 0; i < points; i++) {

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

    pass_data my_data;
    for (int i = 0; i < points; i++) {
        my_data.points_array[i] = points_array[i];
    }

    perform(&my_data);

    SetTraceLogLevel(LOG_WARNING);
    SetTargetFPS(30);
    InitWindow(height, width, "HELLO");

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);


        DrawLine(points_array[0].x, points_array[0].y, points_array[1].x, points_array[1].y, RED);

        EndDrawing();

    }

    return 0;
}
