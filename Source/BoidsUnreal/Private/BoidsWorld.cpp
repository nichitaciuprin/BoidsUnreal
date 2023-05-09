#include "BoidsWorld.h"

GameWorld GameWorld_Create()
{
    GameWorld gameWorld;

    Subgen subgen = Subgen_Create(0);
    gameWorld.aabb.p0 = {-25,-25};
    gameWorld.aabb.p1 = { 25, 25};
	for (int i = 0; i < GAMEWORLD_BOIDSCOUNT; i++)
		gameWorld.boids[i] = Boid_Create(&gameWorld.aabb,&subgen);

    return gameWorld;
}
void GameWorld_Update(GameWorld* gameWorld, float deltaTime)
{
    Boid_Update(gameWorld->boids,GAMEWORLD_BOIDSCOUNT,&gameWorld->aabb,deltaTime);
}