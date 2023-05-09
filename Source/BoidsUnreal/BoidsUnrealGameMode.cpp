// Copyright Epic Games, Inc. All Rights Reserved.

#include "BoidsUnrealGameMode.h"
#include "BoidsUnrealCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABoidsUnrealGameMode::ABoidsUnrealGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
