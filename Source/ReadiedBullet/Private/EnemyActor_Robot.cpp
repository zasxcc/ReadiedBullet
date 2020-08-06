// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor_Robot.h"

// Sets default values
AEnemyActor_Robot::AEnemyActor_Robot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RC = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	Head = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshHead"));
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshBody"));

	RootComponent = RC;
	Head->SetupAttachment(Body);
	fireTime = 0.0f;
}

// Called when the game starts or when spawned
void AEnemyActor_Robot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyActor_Robot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector playerLoc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(Head->GetComponentLocation(), playerLoc);
	Head->SetWorldRotation(rot);

	fireTime += DeltaTime;

	if (fireTime > 1.6f)
	{
		Fire();
		fireTime = 0.0f;
	}
	
}

void AEnemyActor_Robot::Fire()
{
	/*AudioComponent->AttenuationSettings;
	AudioComponent->SetSound(FireCue);
	AudioComponent->Play();*/

	FVector EyeLocation;
	FRotator EyeRotation;

	this->GetActorEyesViewPoint(EyeLocation, EyeRotation);


	FVector ShotDirection = EyeRotation.Vector();

	// Bullet Spread
	float HalfRad = FMath::DegreesToRadians(BulletSpread);
	ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad);

	FVector TraceEnd = EyeLocation + (ShotDirection * 10000);
	if (ProjectileClass)
	{
		//무기 위치 받아서 저장
		FVector MuzzleLocation = Head->GetSocketLocation("Gun_EndSocket");
		//FRotator MuzzleRotation = MeshComp->GetSocketRotation("MuzzleFlashSocket");;

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		FVector meshLoc = Head->GetComponentLocation();
		meshLoc.Z = meshLoc.Z + 250;
		// spawn the projectile at the muzzle
		GetWorld()->SpawnActor<AActor>(ProjectileClass, meshLoc, Head->GetComponentRotation(), ActorSpawnParams);
	}

	//LastFireTime = GetWorld()->TimeSeconds;

}


void AEnemyActor_Robot::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	
}