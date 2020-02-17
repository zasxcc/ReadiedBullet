// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "BulletComp_BOX.generated.h"

UCLASS()
class READIEDBULLET_API ABulletComp_BOX : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletComp_BOX();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void BoxCompOnClicked(class UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void BoxCompOnReleased(class UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void OnOverlapBegin_LeftBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd_LeftBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UStaticMeshComponent* BoxComp;


	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UStaticMeshComponent* LeftBox;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UStaticMeshComponent* RightBox;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UStaticMeshComponent* UpBox;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UStaticMeshComponent* DownBox;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UStaticMeshComponent* FrontBox;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UStaticMeshComponent* BackBox;


	bool bOnCursor;
	FVector NewWorldLocation;
	FHitResult HitResult;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
