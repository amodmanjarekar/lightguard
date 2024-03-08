#include <raylib.h>
#include <raymath.h>
#include <math.h>
#include "constants.h"

typedef struct Quad
{
    Vector3 x1;
    Vector3 x2;
    Vector3 y1;
    Vector3 y2;
} Quad;

Quad getQuad(Vector2 p1, Vector2 p2)
{
    return (Quad){
        .x1 = (Vector3){.x = p1.x, .y = p1.y, .z = -5},
        .x2 = (Vector3){.x = p1.x, .y = p1.y, .z = 5},
        .y1 = (Vector3){.x = p2.x, .y = p2.y, .z = -5},
        .y2 = (Vector3){.x = p2.x, .y = p2.y, .z = 5}};
}

void drawQuad(Quad quad) // debug only
{
    DrawLine(quad.x1.x, quad.x1.y, quad.x2.x, quad.x2.y, WHITE);
    DrawLine(quad.x2.x, quad.x2.y, quad.y2.x, quad.y2.y, WHITE);
    DrawLine(quad.y2.x, quad.y2.y, quad.y1.x, quad.y1.y, WHITE);
    DrawLine(quad.y1.x, quad.y1.y, quad.x1.x, quad.x1.y, WHITE);
}

Vector3 getClosestHit(Vector3 source, Vector3 hits[])
{
    float minDistance = width;
    int minIndex = 0;
    for (int i = 0; i < num_points; i++)
    {
        if (hits[i].z == 0)
        {
            int temp = Vector3Distance(source, hits[i]);
            if (temp < minDistance)
            {
                minDistance = temp;
                minIndex = i;
            }
        }
    }

    return hits[minIndex];
}

void raycastAtPos(Vector3 rayPos, Vector2 collisionPoints[num_points])
{
    Quad quads[num_points];

    for (int i = 0; i < num_points; i++)
    {
        if (i == num_points - 1)
        {
            quads[i] = getQuad(collisionPoints[i], collisionPoints[0]);
        }
        else
        {
            quads[i] = getQuad(collisionPoints[i], collisionPoints[i + 1]);
        }
    }

    int density = num_rays;
    int num, x, y;
    for (num = 0; num < density * 4; num++)
    {

        if (num < density * 2)
        {
            x = num - density;
            if (x > 0)
            {
                y = density - x;
            }
            else
            {
                y = density + x;
            }
        }
        else
        {
            x = (density * 3) - num;
            if (x < 0)
            {
                y = -density - x;
            }
            else
            {
                y = x - density;
            }
        }

        Vector3 hits[num_points];
        for (int i = 0; i < num_points; i++)
        {
            hits[i] = (Vector3){.x = 0, .y = 0, .z = -1};
        }
        Vector3 hitPoint;

        for (int j = 0; j < num_points; j++)
        {
            RayCollision col = GetRayCollisionQuad(
                (Ray){
                    .position = rayPos,
                    .direction = (Vector3){.x = x, .y = y, .z = 0}},
                quads[j].x1,
                quads[j].y2,
                quads[j].y1,
                quads[j].x2);

            if (col.hit == true)
            {
                // printf("%d hit!\n", j);
                hits[j] = col.point;
            }
        }

        hitPoint = getClosestHit(rayPos, hits);

        // DrawRay(
        //     (Ray){
        //         .position = rayPos,
        //         .direction = (Vector3){.x = x, .y = y, .z = 0}},
        //     RED);
        DrawLine(rayPos.x, rayPos.y, hitPoint.x, hitPoint.y, BLUE);
    }
}
