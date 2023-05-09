// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoidsWorld.h"
#include "BoidBody.h"

#include "Engine/EngineTypes.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Main.generated.h"

UCLASS()
class BOIDSUNREAL_API AMain : public APawn
{
	GENERATED_BODY()

public:
	AMain();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	GameWorld gameWorld = GameWorld_Create();
	ABoidBody* boidBodys[GAMEWORLD_BOIDSCOUNT];
};
