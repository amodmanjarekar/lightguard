#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "./lib/raycast.c"
#include "./lib/random_points.c"
#include "./lib/constants.h"

extern void create_polygon(pass_data *my_data);

int main() {

    Vector2 points_array[num_points];
    pass_data my_data;

    srand(time(NULL));

    generate_random_points(points_array);

    copy_to_pass_data(points_array, &my_data);

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
