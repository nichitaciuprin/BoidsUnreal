// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidBody.h"

ABoidBody::ABoidBody()
{
 	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		float size = 0.70f;
		VisualMesh->SetWorldScale3D(FVector(size,size,size));
	}
}
void ABoidBody::BeginPlay()
{
	Super::BeginPlay();
}
void ABoidBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}