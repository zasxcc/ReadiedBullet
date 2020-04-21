// Fill out your copyright notice in the Description page of Project Settings.


#include "RBWeapon.h"

static int32 DebugWeaponDrawing = 0;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(
	TEXT("COOP.DebugWeapon"),
	DebugWeaponDrawing,
	TEXT("Draw Debug Lines for Weapon"),
	ECVF_Cheat
);

// Sets default values
ARBWeapon::ARBWeapon()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MuzzleSocketName = "MuzzleFlashSocket";
	TracerTargetName = "Target";
	//

	static ConstructorHelpers::FObjectFinder<USoundBase>FIRESOUND(TEXT("/Game/Sound/GunFire.GunFire"));
	if (FIRESOUND.Succeeded())
	{
		FireCue = FIRESOUND.Object;
	}


	// 오디오 컴포넌트 추가
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerAudio"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(RootComponent);

	BaseDamage = 20.0f;
	RateOfFire = 400;
}

void ARBWeapon::BeginPlay()
{
	Super::BeginPlay();

	TimeBetweenShots = 60 / RateOfFire;
}


void ARBWeapon::Fire()
{
	AActor* MyOwner = GetOwner();

	AudioComponent->SetSound(FireCue);
	AudioComponent->Play();

	if (ProjectileClass)
	{
		//무기 위치 받아서 저장
		FVector MuzzleLocation = MeshComp->GetSocketLocation("MuzzleFlashSocket");
		//FRotator MuzzleRotation = MeshComp->GetSocketRotation("MuzzleFlashSocket");;

		FVector EyeLocation;
		FRotator EyeRotation;

		//엑터가 바라보는 위치, 방향 저장
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
		
		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, EyeRotation, ActorSpawnParams);
	}

	//카메라 흔들기
	APawn* MyOwner2 = Cast<APawn>(GetOwner());
	if (MyOwner2)
	{
		APlayerController* PC = Cast<APlayerController>(MyOwner2->GetController());
		if (PC)
		{
			PC->ClientPlayCameraShake(FireCamShake);
		}
	}

}

void ARBWeapon::StartFire()
{
	float FireDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.0f);
	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &ARBWeapon::Fire, TimeBetweenShots, true, FireDelay);
}

void ARBWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}


void ARBWeapon::PlayFireEffects(FVector TraceEnd)
{
	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
	}


	if (TracerEffect)
	{
		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
		UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);
		if (TracerComp)
		{
			TracerComp->SetVectorParameter(TracerTargetName, TraceEnd);
		}
	}

}