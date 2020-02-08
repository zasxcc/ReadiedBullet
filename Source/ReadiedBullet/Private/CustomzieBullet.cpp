// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomzieBullet.h"

// Sets default values
ACustomzieBullet::ACustomzieBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ACustomzieBullet::BeginPlay()
{
	Super::BeginPlay();
	//MeshComp->OnBeginCursorOver.Broadcast();
}

// Called every frame
void ACustomzieBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

