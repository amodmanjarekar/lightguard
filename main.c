#include <raylib.h>

#define height 1024
#define width 720

int main() {

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(height, width, "HELLO");

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();

    }

    return 0;
}
