// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReadiedBullet/RBCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HomingMissile.generated.h"

UCLASS()
class READIEDBULLET_API AHomingMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHomingMissile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StaticMesh")
	UStaticMeshComponent* Head;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StaticMesh")
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StaticMesh")
	UProjectileMovementComponent* ProjectileMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	USoundBase* MissileCue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	class UAudioComponent* AudioComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float homingTimer;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
