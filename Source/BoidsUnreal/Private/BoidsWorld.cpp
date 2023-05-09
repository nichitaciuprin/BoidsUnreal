#include "BoidsWorld.h"

BoidsWorld BoidsWorld_Create()
{
    BoidsWorld gameWorld;

    Subgen subgen = Subgen_Create(0);
    gameWorld.aabb.p0 = {-25,-25};
    gameWorld.aabb.p1 = { 25, 25};
	for (int i = 0; i < BOIDSWORLD_BOIDSCOUNT; i++)
		gameWorld.boids[i] = Boid_Create(&gameWorld.aabb,&subgen);

    return gameWorld;
}
void BoidsWorld_Update(BoidsWorld* gameWorld, float deltaTime)
{
    Boid_Update(gameWorld->boids,BOIDSWORLD_BOIDSCOUNT,&gameWorld->aabb,deltaTime);
}