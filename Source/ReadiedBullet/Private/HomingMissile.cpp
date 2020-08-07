// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingMissile.h"

// Sets default values
AHomingMissile::AHomingMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshHead"));
	//Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshBody"));
	ProjectileMove = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	
	RootComponent = Head;
	homingTimer = 0.0f;

}

// Called when the game starts or when spawned
void AHomingMissile::BeginPlay()
{
	Super::BeginPlay();
	

	ProjectileMove->bIsHomingProjectile = false;
}

// Called every frame
void AHomingMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	homingTimer += 1.0f;

	if (homingTimer > 200.0f && homingTimer < 202.0f)
	{
		ARBCharacter* playerCharacter = Cast<ARBCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		USceneComponent* target = playerCharacter->GetRootComponent();
		ProjectileMove->HomingTargetComponent = target;
		ProjectileMove->bIsHomingProjectile = true;
		homingTimer = 300.0f;
	}
}

