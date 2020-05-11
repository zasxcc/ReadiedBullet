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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		TArray<FTransform>  InstanceBoxSlot2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		TArray<FTransform>  InstanceCylinderSlot2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		TArray<FTransform>  InstanceSphereSlot2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		TArray<FTransform>  InstanceBoxSlot3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		TArray<FTransform>  InstanceCylinderSlot3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		TArray<FTransform>  InstanceSphereSlot3;

	TArray<FTransform> GetInstanceBoxSlot1();
	TArray<FTransform> GetInstanceCylinderSlot1();
	TArray<FTransform> GetInstanceSphereSlot1();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	float SaveSlot1_InstanceX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	float SaveSlot1_InstanceY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	float SaveSlot1_InstanceZ;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		float SaveSlot2_InstanceX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		float SaveSlot2_InstanceY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		float SaveSlot2_InstanceZ;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		float SaveSlot3_InstanceX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		float SaveSlot3_InstanceY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
		float SaveSlot3_InstanceZ;


	int32 SelectSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	float PlayerMaxHP = 100.0f;


	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	int32 BulletImpactSolt1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	int32 BulletImpactSolt2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	int32 BulletImpactSolt3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armo")
	int32 CurrentArmo = 30;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armo")
	int32 Margazine = 90;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armo")
	bool IsReloading;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Path")
	TArray<FVector> PathArray1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Path")
	TArray<FVector> PathArray2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Path")
	TArray<FVector> PathArray3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Path")
	bool IsPathMade1 = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Path")
	bool IsPathMade2 = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Path")
	bool IsPathMade3 = false;
};
