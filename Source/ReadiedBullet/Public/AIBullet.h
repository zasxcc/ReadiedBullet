// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AIBullet.generated.h"

UCLASS()
class READIEDBULLET_API AAIBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIBullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMeshComp")
	UStaticMeshComponent* bulletBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMeshComp")
	UStaticMeshComponent* bulletHead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMeshComp")
	UBoxComponent* boxColl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileMovement")
	UProjectileMovementComponent* projectile;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

};
