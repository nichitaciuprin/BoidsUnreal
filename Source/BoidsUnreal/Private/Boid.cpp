#include "Boid.h"
#include "AABB.h"
#include <math.h>
#include <memory.h>

#define scale 1
const float minSpeed = 9*scale;
const float maxSpeed = 15*scale;
const float range_1 = 5*scale;
const float range_2 = 5*scale;
const float range_3 = 2*scale;
#define rangeSquared_1 range_1*range_1
#define rangeSquared_2 range_2*range_2
#define rangeSquared_3 range_3*range_3
const float power1 = 0.01*scale;
const float power2 = 0.01*scale;
const float power3 = 0.04*scale;
const float acc = 10*scale;

void CalculatePair(int boidIndex1, int boidIndex2, Boid* boids)
{
    Boid* boid1 = &boids[boidIndex1];
    Boid* boid2 = &boids[boidIndex2];

    MyVector2 diff = MyVector2_Sub(boid1->pos,boid2->pos);
    float distSquared = diff.x*diff.x + diff.y*diff.y;
    float dist = sqrtf(distSquared);

    // COHESION
    if (distSquared >= rangeSquared_1) return;

    boid1->vec_1 = MyVector2_Add(boid1->vec_1,boid2->pos); boid1->count_1++;
    boid2->vec_1 = MyVector2_Add(boid2->vec_1,boid1->pos); boid2->count_1++;

    // ALIGHMENT
    if (distSquared >= rangeSquared_2) return;

    boid1->vec_2 = MyVector2_Add(boid1->vec_2,boid2->vel); boid1->count_2++;
    boid2->vec_2 = MyVector2_Add(boid2->vec_2,boid1->vel); boid2->count_2++;

    // SEPARATION
    if (distSquared >= rangeSquared_3) return;

    float normFraction = 1.0f/dist;
    MyVector2 normDiff = { diff.x*normFraction, diff.y*normFraction };
    float dist2 = range_3 - dist;
    normDiff = MyVector2_Mul(normDiff,dist2);

    boid1->vec_3 = MyVector2_Add(boid1->vec_3,normDiff);
    boid2->vec_3 = MyVector2_Add(boid2->vec_3,MyVector2_Negate(normDiff));
}
MyVector2 TargetVelocity(Boid* boid)
{
    MyVector2 result = boid->vel;

    MyVector2 vec_1 = boid->vec_1;
    MyVector2 vec_2 = boid->vec_2;
    MyVector2 vec_3 = boid->vec_3;
    int count_1 = boid->count_1;
    int count_2 = boid->count_2;

    if (count_1 != 0)
    {
        vec_1 = MyVector2_Div(vec_1,count_1);
        vec_1 = MyVector2_Sub(vec_1,boid->pos);
    }
    if (count_2 != 0)
    {
        vec_2 = MyVector2_Div(vec_2,count_2);
        vec_2 = MyVector2_Sub(vec_2,boid->vel);
    }

    vec_1 = MyVector2_Mul(vec_1,power1);
    vec_2 = MyVector2_Mul(vec_2,power2);
    vec_3 = MyVector2_Mul(vec_3,power3);

    result = MyVector2_Add(result,vec_1);
    result = MyVector2_Add(result,vec_2);
    result = MyVector2_Add(result,vec_3);

    result = MyVector2_ClampLength(result,minSpeed,maxSpeed);

    return result;
}

Boid Boid_Create(AABB* aabb, Subgen* subgen)
{
    float randSpeed = Subgen_Range(subgen,minSpeed,maxSpeed);
    MyVector2 randDirection = MyVector2_RandNormDir(subgen);

    MyVector2 pos = AABB_RandPointInside(subgen,aabb);
    MyVector2 vel = MyVector2_Mul(randDirection,randSpeed);

    Boid boid;
    boid.pos = pos;
    boid.vel = vel;

    return boid;
}
void Boid_Update(Boid* boids, int boidsLength, AABB* aabb, float deltaTime)
{
    int length = boidsLength;

    for (int i = 0; i < length; i++)
    {
        boids[i].count_1 = 0;
        boids[i].count_2 = 0;
        boids[i].vec_1 = { 0,0 };
        boids[i].vec_2 = { 0,0 };
        boids[i].vec_3 = { 0,0 };
    }

    // ALL UNIQUE PAIRS
    for (int i = 0;   i < length; i++)
    for (int j = i+1; j < length; j++)
        CalculatePair(i,j,boids);

    for (int i = 0; i < length; i++)
    {
        Boid* boid = &boids[i];

        MyVector2 targetVelocity = TargetVelocity(boid);
        MyVector2 newVelocity = MyVector2_MoveTowards(boid->vel,targetVelocity,acc*deltaTime);
        boid->pos = MyVector2_PositionUpdate_Advanced(boid->pos,boid->vel,boid->vel,deltaTime);
        boid->vel = newVelocity;

        boid->pos = AABB_WrapAround(aabb,boid->pos);
    }
}
void Boid_Print(Boid* boid)
{
    MyVector2_PrintVector2Hex(boid->pos);
    MyVector2_PrintVector2Hex(boid->vel);
}