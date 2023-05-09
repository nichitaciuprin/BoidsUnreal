#pragma once

#include "MyVector2.h"
#include "AABB.h"
#include "Subgen.h"

typedef struct Boid
{
    MyVector2 pos;
    MyVector2 vel;
    MyVector2 vec_1;
    MyVector2 vec_2;
    MyVector2 vec_3;
    int count_1;
    int count_2;
} Boid;

Boid Boid_Create(AABB* aabb, Subgen* subgen);
void Boid_Update(Boid* boids, int boidsLength, AABB* aabb, float deltaTime);
void Boid_Print(Boid* boid);