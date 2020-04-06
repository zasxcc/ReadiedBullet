// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ReadiedBullet.h"
#include "GameFramework/GameModeBase.h"
#include "ReadiedBulletGameMode.generated.h"

UCLASS(minimalapi)
class AReadiedBulletGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AReadiedBulletGameMode();
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override; //�÷��̾ �α����� �Ϸ��ϸ� ȣ��Ǵ� �̺�Ʈ �Լ�

	


};



