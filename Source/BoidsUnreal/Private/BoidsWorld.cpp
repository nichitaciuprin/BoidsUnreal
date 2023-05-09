#include "BoidsWorld.h"

BoidsWorld BoidsWorld_Create()
{
    BoidsWorld boidsWorld;

    Subgen subgen = Subgen_Create(0);
    boidsWorld.aabb.p0 = {-25,-25};
    boidsWorld.aabb.p1 = { 25, 25};
	for (int i = 0; i < BOIDSWORLD_BOIDSCOUNT; i++)
		boidsWorld.boids[i] = Boid_Create(&boidsWorld.aabb,&subgen);

    return boidsWorld;
}
void BoidsWorld_Update(BoidsWorld* boidsWorld, float deltaTime)
{
    Boid_Update(boidsWorld->boids,BOIDSWORLD_BOIDSCOUNT,&boidsWorld->aabb,deltaTime);
}