// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GameFramework/Actor.h"
#include "EnemyActor_Dragon.generated.h"


UCLASS()
class READIEDBULLET_API AEnemyActor_Dragon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor_Dragon();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
	UCapsuleComponent* Capsule;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Visual)
	USkeletalMeshComponent* Mesh;
};