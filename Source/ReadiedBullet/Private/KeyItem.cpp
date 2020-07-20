// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyItem.h"

// Sets default values
AKeyItem::AKeyItem()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	CapCom = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleColl"));
	CapCom->SetupAttachment(StaticMesh);
	CapCom->OnComponentBeginOverlap.AddDynamic(this, &AKeyItem::BeginOverlap);

}

// Called when the game starts or when spawned
void AKeyItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Log Message"));

}


