// Fill out your copyright notice in the Description page of Project Settings.

#include "Main.h"

AMain::AMain()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AMain::BeginPlay()
{
	Super::BeginPlay();
	for (size_t i = 0; i < GAMEWORLD_BOIDSCOUNT; i++)
	{
		FVector location = FVector(0.0f, 0.0f, 0.0f);
		FRotator rotation = FRotator(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters spawnInfo;
		boidBodys[i] = (ABoidBody*)GetWorld()->SpawnActor<ABoidBody>(location, rotation, spawnInfo);
	}
}
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameWorld_Update(&gameWorld,DeltaTime);
	for (size_t i = 0; i < GAMEWORLD_BOIDSCOUNT; i++)
	{
		float scale = 50;
		float waverFrequency = 70;
		float waveHeight = 15;
		auto x = gameWorld.boids[i].pos.x*scale;
		auto y = gameWorld.boids[i].pos.y*scale;
		auto z = (FMath::Sin(x/waverFrequency)+FMath::Cos(y/waverFrequency))*waveHeight;
		// auto z = (FMath::Cos(y/waverFrequency))*waveHeight;
		FVector location = FVector(x, y, z);
		FHitResult hit;
		boidBodys[i]->SetActorLocation(location,false,&hit,ETeleportType::None);
	}
}
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

