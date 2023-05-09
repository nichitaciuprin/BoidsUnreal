#pragma once

#include "AABB.h"
#include "Boid.h"

#define BOIDSWORLD_BOIDSCOUNT 300

typedef struct BoidsWorld
{
    AABB aabb;
    Boid boids[BOIDSWORLD_BOIDSCOUNT];
} BoidsWorld;

BoidsWorld BoidsWorld_Create();
void BoidsWorld_Update(BoidsWorld* boidsWorld, float deltaTime);