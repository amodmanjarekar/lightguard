#include <raylib.h>

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define height 1024
#define width 720
#define num_points 30
#define num_rays 100;

typedef struct pass_data
{
    Vector2 points_array[num_points];
} pass_data;

#endif // !CONSTANTS
