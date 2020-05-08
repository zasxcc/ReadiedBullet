// Fill out your copyright notice in the Description page of Project Settings.


#include "RBCharacter.h"


// Sets default values
ARBCharacter::ARBCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(TEXT("Alive"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;


	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerAudio"));
	AudioComponent->bAutoActivate = false;


	static ConstructorHelpers::FObjectFinder<UAnimMontage> RELOAD(TEXT("AnimMontage'/Game/Animation/Reload_Montage.Reload_Montage'"));
	if (RELOAD.Succeeded())
	{
		ReloadMontage = RELOAD.Object;
	}

	// static ConstructorHelpers::FObjectFinder<USoundBase>RELOADSOUND(TEXT("SoundWave'/Game/Sound/Reload.Reload'"));
	// if (RELOADSOUND.Succeeded())
	// {
	// 	ReloadCue = RELOADSOUND.Object;
	// }

	//¾É±â È°¼ºÈ­
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);
	
	ZoomedFOV = 40.0f;
	ZoomInterpSpeed = 20;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARBCharacter::BeginOverlap);
	WeaponAttachSocketName = "WeaponSocket";

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("RBCharacter"));


	//////////////////Path ÀÛ¾÷///////////////////////////////
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PATH(TEXT("/Game/StarterContent/Props/SM_Couch"));
	for (int32 i = 0; i < 100; i++)
	{
		FName name = *FString::Printf(TEXT("Path %i"), i);
		PathMeshArray.Add(CreateDefaultSubobject<UStaticMeshComponent>(name));
		if (PATH.Succeeded())
		{
			PathMeshArray[i]->SetStaticMesh(PATH.Object);
			PathMeshArray[i]->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
			PathMeshArray[i]->AttachToComponent(CameraComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
	////////////////////////////////
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

	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	MaxHP = GameInstance->PlayerMaxHP;
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

	if (CurrentProjectile)
	{
		CurrentProjectile->SelectBulletSlot = 1;
	}
}

void ARBCharacter::SelectSlot2()
{
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SelectSlot = 2;

	if (CurrentProjectile)
	{
		CurrentProjectile->SelectBulletSlot = 2;
	}
}

void ARBCharacter::SelectSlot3()
{
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SelectSlot = 3;

	if (CurrentProjectile)
	{
		CurrentProjectile->SelectBulletSlot = 3;
	}
}

void ARBCharacter::StartFire()
{
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if (IsReloading == false) {
		if (CurrentWeapon)
		{
			CurrentWeapon->StartFire();
		}
	}
}

void ARBCharacter::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}

void ARBCharacter::Reload()
{
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	IsReloading = true;
	AudioComponent->SetSound(ReloadCue);
	AudioComponent->Play();

	if(CurrentWeapon)
	{
		CurrentWeapon->Reload();
		PlayAnimMontage(ReloadMontage, 1.0f);
	}
}

// Called every frame
void ARBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;
	float NewFOV = FMath::FInterpTo(CameraComp->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);

	CameraComp->SetFieldOfView(NewFOV);

	if (IsReloading == true)
	{
		ReloadCount += DeltaTime;
		//UE_LOG(LogTemp, Warning, TEXT("%f"), ReloadCount);
		if (ReloadCount >= 3.0f)
		{
			IsReloading = false;
			ReloadCount = 0.0f;
		}
	}

	////Path ÀÛ¾÷
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(GameInstance->IsPathMade == true)
	{
		for(int i = 0; i<100; ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("%f,  %f,  %f"), GameInstance->PathArray[i].X, GameInstance->PathArray[i].Y, GameInstance->PathArray[i].Z);
			PathMeshArray[i]->SetRelativeLocation(FVector(GameInstance->PathArray[i].X, GameInstance->PathArray[i].Y, GameInstance->PathArray[i].Z));
		}
		GameInstance->IsPathMade = false;
	}
	//////////////////////
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

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ARBCharacter::Reload);

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


void ARBCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->PlayerMaxHP -= 10;
	MaxHP = GameInstance->PlayerMaxHP;

	UE_LOG(LogTemp, Warning, TEXT("MaxHP : %f,  InstanceHP : %f"), MaxHP, GameInstance->PlayerMaxHP);
}