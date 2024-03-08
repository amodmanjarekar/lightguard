#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./lib/raycast.c"
#include "./lib/random_points.c"
#include "./lib/handle_guards.c"
#include "./lib/constants.h"

extern void create_polygon(pass_data *my_data);

int main()
{

    Vector2 points_array[num_points];
    pass_data my_data;

    int max_guards = floor(num_points / 3);
    int used_guards = 0;

    Vector3 guard_points[max_guards];

    initialize_guards(guard_points, max_guards);

    srand(time(NULL));

    generate_random_points(points_array);

    copy_to_pass_data(points_array, &my_data);

    create_polygon(&my_data);

    SetTraceLogLevel(LOG_WARNING);
    SetTargetFPS(60);
    InitWindow(height, width, "HELLO");

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < num_points; i++)
        {
            DrawCircle(my_data.points_array[i].x, my_data.points_array[i].y, 4, PURPLE);
        }

        for (int i = 0; i < (num_points - 1); i++)
        {
            DrawLine(my_data.points_array[i].x,
                     my_data.points_array[i].y,
                     my_data.points_array[i + 1].x,
                     my_data.points_array[i + 1].y,
                     GREEN);
        }

        DrawLine(my_data.points_array[num_points - 1].x,
                 my_data.points_array[num_points - 1].y,
                 my_data.points_array[0].x,
                 my_data.points_array[0].y,
                 GREEN);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true)
        {
            add_guard(guard_points, &used_guards, max_guards);
        }

        if (guard_points > 0)
        {
            for (int i = 0; i < used_guards; i++)
            {
                raycastAtPos(guard_points[i], my_data.points_array);
            }
        }

        EndDrawing();
    }

    return 0;
}
