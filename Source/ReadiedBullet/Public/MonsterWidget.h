// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "MonsterWidget.generated.h"

/**
 * 
 */
UCLASS()
class READIEDBULLET_API UMonsterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	class UProgressBar* HPProgressBar;

protected:
	virtual void NativeConstruct() override;
};
