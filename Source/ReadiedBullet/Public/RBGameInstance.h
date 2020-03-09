// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RBGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class READIEDBULLET_API URBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	//URBGameInstance();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	TArray<FTransform>  InstanceBoxSlot1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	TArray<FTransform>  InstanceCylinderSlot1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	TArray<FTransform>  InstanceSphereSlot1;

};
