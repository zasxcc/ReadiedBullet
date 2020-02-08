// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "CustomzieBullet.generated.h"

UCLASS()
class READIEDBULLET_API ACustomzieBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomzieBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
