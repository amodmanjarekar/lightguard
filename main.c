#include <raylib.h>

#define height 1024
#define width 720

int main() {

    InitWindow(height, width, "HELLO");

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();

    }

    return 0;
}
