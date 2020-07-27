// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBullet.h"

// Sets default values
AAIBullet::AAIBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bulletBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_Body"));
	bulletHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_Head"));
	projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	boxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionCom"));

	RootComponent = boxColl;

}

// Called when the game starts or when spawned
void AAIBullet::BeginPlay()
{
	Super::BeginPlay();
	boxColl->OnComponentBeginOverlap.AddDynamic(this, &AAIBullet::BeginOverlap);
}

// Called every frame
void AAIBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("DoorLog"));
}