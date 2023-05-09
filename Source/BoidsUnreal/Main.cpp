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
		auto x = gameWorld.boids[i].pos.x*50;
		auto y = gameWorld.boids[i].pos.y*50;
		FVector location = FVector(x, y, 0);
		FHitResult hit;
		boidBodys[i]->SetActorLocation(location,false,&hit,ETeleportType::None);
	}
}
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

