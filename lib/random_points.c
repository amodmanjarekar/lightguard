#include <stdlib.h>
#include <stdbool.h>
#include "./constants.h"

bool is_not_unique = true;

void generate_random_points(Vector2 *points_array) {

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

}

void copy_to_pass_data(Vector2 *points_array, pass_data *my_data) {

    for (int i = 0; i < num_points; i++) {
        my_data->points_array[i] = points_array[i];
    }

}
