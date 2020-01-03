// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ReadiedBulletGameMode.h"
#include "ReadiedBulletCharacter.h"
#include "UObject/ConstructorHelpers.h"

AReadiedBulletGameMode::AReadiedBulletGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
