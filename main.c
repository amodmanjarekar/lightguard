#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "./lib/raycast.c"

#define height 1024
#define width 720
#define num_points 10

typedef struct pass_data {
    Vector2 points_array[num_points];
}pass_data;

extern void create_polygon(pass_data *d);

int main() {

    srand(time(NULL));

    bool is_not_unique = true;
    Vector2 points_array[num_points];

    for (int t = 0; t < num_points; t++) {

        is_not_unique = true;

        while (is_not_unique) {

            int random_x = rand() % (height);
            int random_y = rand() % (width);

            for (int i = 0; i < num_points; i++) {

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

    for (int i = 0; i < num_points; i++) {
        my_data.points_array[i] = points_array[i];
    }

    create_polygon(&my_data);

    SetTraceLogLevel(LOG_WARNING);
    SetTargetFPS(30);
    InitWindow(height, width, "HELLO");

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < num_points; i++) {
            DrawCircle(my_data.points_array[i].x, my_data.points_array[i].y, 4, PURPLE);
        }

        for (int i = 0; i < (num_points-1); i++) {
            DrawLine(my_data.points_array[i].x, my_data.points_array[i].y, my_data.points_array[i+1].x, my_data.points_array[i+1].y, GREEN);
        }

        DrawLine(my_data.points_array[num_points-1].x, my_data.points_array[num_points-1].y, my_data.points_array[0].x, my_data.points_array[0].y, GREEN);

        EndDrawing();

    }

    return 0;
}
