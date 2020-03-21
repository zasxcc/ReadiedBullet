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
	void SetInstanceBoxSlot1(TArray<FTransform> BoxSlot);
	void SetInstanceCylinderSlot1(TArray<FTransform> CylinderSlot);
	void SetInstanceSphereSlot1(TArray<FTransform> SphereSlot);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	TArray<FTransform>  InstanceBoxSlot1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	TArray<FTransform>  InstanceCylinderSlot1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	TArray<FTransform>  InstanceSphereSlot1;

	TArray<FTransform> GetInstanceBoxSlot1();
	TArray<FTransform> GetInstanceCylinderSlot1();
	TArray<FTransform> GetInstanceSphereSlot1();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	float InstanceX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	float InstanceY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	float InstanceZ;

protected:
	

	

};
