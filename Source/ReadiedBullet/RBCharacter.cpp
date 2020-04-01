// Fill out your copyright notice in the Description page of Project Settings.


#include "RBCharacter.h"


// Sets default values
ARBCharacter::ARBCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	//¾É±â È°¼ºÈ­
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	ZoomedFOV = 65.0f;
	ZoomInterpSpeed = 20;

	WeaponAttachSocketName = "WeaponSocket";

}

// Called when the game starts or when spawned
void ARBCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultFOV = CameraComp->FieldOfView;

	//Spawn a Default Weapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentWeapon = GetWorld()->SpawnActor<ARBWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
	}
}

void ARBCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void ARBCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void ARBCharacter::BeginCrouch()
{
	//¾É±â 
	Crouch();
}

void ARBCharacter::EndCrouch()
{
	//¾É±â Ç®±â
	UnCrouch();
}

void ARBCharacter::BeginZoom()
{
	bWantsToZoom = true;
}

void ARBCharacter::EndZoom()
{
	bWantsToZoom = false;
}

void ARBCharacter::SelectSlot1()
{
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SelectSlot = 1;
}

void ARBCharacter::SelectSlot2()
{
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SelectSlot = 2;
}

void ARBCharacter::SelectSlot3()
{
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SelectSlot = 3;
}

void ARBCharacter::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}

void ARBCharacter::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}

// Called every frame
void ARBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;
	float NewFOV = FMath::FInterpTo(CameraComp->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);

	CameraComp->SetFieldOfView(NewFOV);

}

// Called to bind functionality to input
void ARBCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARBCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARBCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ARBCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ARBCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ARBCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ARBCharacter::EndCrouch);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ARBCharacter::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ARBCharacter::EndZoom);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARBCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ARBCharacter::StopFire);

	PlayerInputComponent->BindAction("Slot1", IE_Pressed, this, &ARBCharacter::SelectSlot1);
	PlayerInputComponent->BindAction("Slot2", IE_Pressed, this, &ARBCharacter::SelectSlot2);
	PlayerInputComponent->BindAction("Slot3", IE_Pressed, this, &ARBCharacter::SelectSlot3);
}

FVector ARBCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}


FRotator ARBCharacter::GetCamRotator()
{
	return CameraComp->GetRelativeRotation();
}
