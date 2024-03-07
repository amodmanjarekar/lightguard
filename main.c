#include <raylib.h>
#include "raycast.c"

#define height 1024
#define width 720

int main()
{

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(height, width, "HELLO");
    SetTargetFPS(12);

    int guardX, guardY;
    bool isLocationSelected = false;

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(BLACK);

        Vector2 points[3] = {
            (Vector2){.x = 100, .y = 100},
            (Vector2){.x = 500, .y = 300},
            (Vector2){.x = 200, .y = 500},
        };

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
