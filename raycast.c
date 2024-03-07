#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEN 3;

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

Vector3 getClosestHit(Vector3 hits[], Vector3 source)
{
  int minIndex;
  float minDist;
  for (int i = 0; i < 3; i++)
  {
    Vector3 pTemp = hits[i];
    float dist = sqrt(pow(pTemp.x - source.x, 2) + pow(pTemp.y - source.y, 2));
    if (pTemp.z != -1)
    {
      minDist = dist;
      minIndex = i;
      if (dist < minDist)
      {
        minDist = dist;
        minIndex = i;
      }
    }
  }

  return hits[minIndex];
}

void raycastAtPos(Vector3 rayPos, Vector2 collisionPoints[3])
{
  Quad quads[3];

  for (int i = 0; i < 3; i++)
  {
    if (i == 2)
    {
      quads[i] = getQuad(collisionPoints[i], collisionPoints[0]);
    }
    else
    {
      quads[i] = getQuad(collisionPoints[i], collisionPoints[i + 1]);
    }
  }

  int density = DEN;
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

    Vector3 hits[3] = {
        (Vector3){.x = 0, .y = 0, .z = -1},
        (Vector3){.x = 0, .y = 0, .z = -1},
        (Vector3){.x = 0, .y = 0, .z = -1},
    };

    for (int j = 0; j < 3; j++)
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

    Vector3 hitPoint = getClosestHit(hits, rayPos);

    // DrawRay( // debug only
    //     (Ray){
    //         .position = rayPos,
    //         .direction = (Vector3){.x = x, .y = y, .z = 0}},
    //     RED);

    DrawLine(rayPos.x, rayPos.y, hitPoint.x, hitPoint.y, BLUE);
  }
}
