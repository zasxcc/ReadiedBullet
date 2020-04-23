// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "BarghestAIController.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(TEXT("Alive"));
	
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(GetMesh());

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 500.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	MaxHP = 1.0f;
	IsDead = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

	AIControllerClass = ABarghestAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::BeginOverlap);
}


// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AEnemyCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UMonsterWidget* MW = Cast<UMonsterWidget>(HPBarWidget->GetUserWidgetObject());
	MaxHP -= 0.2f;
	MW->HPProgressBar->SetPercent(MaxHP);

	if (MaxHP <= 0.01f)
	{
		//여기다가 뒤지는 애니메이션 해주셈
		SetDeadAnim();
	}
}

float AEnemyCharacter::GetFinalAttackRange() const
{
	return 50.f;
}

void AEnemyCharacter::Attack()
{
	// Attack Animation 추가해야 할 부분

	// if (attack animation end?) OnAttackEnd.Broadcast();
}