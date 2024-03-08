#include <raylib.h>
#include "constants.h"

void initialize_guards(Vector3 *guard_points, int max_guards) {
    for (int i = 0; i < max_guards; i++) {
        guard_points[i] = (Vector3){.x = 0, .y = 0, .z = -1};
    }
}

void add_guard(Vector3 *guard_points, int *used_guards, int max_guards) {
    guard_points[(*used_guards)++] = (Vector3){.x = GetMouseX(), .y = GetMouseY(), .z = 0};
    if (*used_guards >= max_guards) {
        used_guards = 0;
        initialize_guards(guard_points, max_guards);
    }
}
