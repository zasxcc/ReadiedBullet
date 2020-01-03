// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ReadiedBulletGameMode.h"
#include "RBCharacter.h"
#include "RBPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AReadiedBulletGameMode::AReadiedBulletGameMode()
{
	DefaultPawnClass = ARBCharacter::StaticClass(); 
	PlayerControllerClass = ARBPlayerController::StaticClass();
}


void AReadiedBulletGameMode::PostLogin(APlayerController* NewPlayer)
{
	
	Super::PostLogin(NewPlayer);
	
}