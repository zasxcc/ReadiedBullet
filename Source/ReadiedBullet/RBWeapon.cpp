// Fill out your copyright notice in the Description page of Project Settings.


#include "RBWeapon.h"
#include "RBCharacter.h"
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
	PrimaryActorTick.bCanEverTick = true;
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
	
	static ConstructorHelpers::FObjectFinder<USoundBase>RELOADSOUND(TEXT("SoundWave'/Game/Sound/Reload.Reload'"));
	if (RELOADSOUND.Succeeded())
	{
		ReloadCue = RELOADSOUND.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundBase>FIREMISSSOUND(TEXT("SoundWave'/Game/Sound/FireMiss.FireMiss'"));
	if (FIREMISSSOUND.Succeeded())
	{
		FireMissCue = FIREMISSSOUND.Object;
	}
	

	// ����� ������Ʈ �߰�
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerAudio"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(RootComponent);

	BaseDamage = 20.0f;
	RateOfFire = 400;
}

void ARBWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CurrentArmo = GameInstance->CurrentArmo;
	Magazine = GameInstance->Margazine;
	
	TimeBetweenShots = 60 / RateOfFire;
}


void ARBWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsReloading == true)
	{
		ReloadCount += DeltaTime;

		if (ReloadCount >= 2)
		{
			IsReloading = false;
			ReloadCount = 0.0f;
			URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstance->IsReloading = IsReloading;
		}
	}


}



void ARBWeapon::Fire()
{
	AActor* MyOwner = GetOwner();
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	
	if(CurrentArmo > 0 && IsReloading == false)
	{
		AudioComponent->SetSound(FireCue);
		AudioComponent->Play();

		if (ProjectileClass)
		{
			//���� ��ġ �޾Ƽ� ����
			FVector MuzzleLocation = MeshComp->GetSocketLocation("MuzzleFlashSocket");
			//FRotator MuzzleRotation = MeshComp->GetSocketRotation("MuzzleFlashSocket");;

			FVector EyeLocation;
			FRotator EyeRotation;

			//���Ͱ� �ٶ󺸴� ��ġ, ���� ����
			MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, EyeRotation, ActorSpawnParams);		
		}

		//ī�޶� ����
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
	
	else
	{
		AudioComponent->SetSound(FireMissCue);
		AudioComponent->Play();
	}

	if(CurrentArmo > 0)
	{
		CurrentArmo--;
	}
	
	GameInstance->CurrentArmo = CurrentArmo;
	UE_LOG(LogTemp, Warning, TEXT("%d / %d"), CurrentArmo, Magazine);
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

void ARBWeapon::Reload()
{
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	IsReloading = true;
	AudioComponent->SetSound(ReloadCue);
	AudioComponent->Play();
	
	Magazine -= 30 - CurrentArmo;
	CurrentArmo = 30;
	
	GameInstance->Margazine = Magazine;
	GameInstance->CurrentArmo = CurrentArmo;
	UE_LOG(LogTemp, Warning, TEXT("%d / %d"), CurrentArmo, Magazine);
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