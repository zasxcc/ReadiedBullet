// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{
	CurrentPawnSpeed = 0.f;
	enemy_state = CharacterAnimState::PEACE;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONGTAGE(TEXT("/Game/QuadrapedCreatures/Barghest/Animations/BARGHEST_biteAggressive_Montage.BARGHEST_biteAggressive_Montage"));
	if (ATTACK_MONGTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONGTAGE.Object;
	}
}

void UEnemyAnimInstance::setState(CharacterAnimState state)
{
	enemy_state = state;
	UE_LOG(LogTemp, Error, TEXT("state changed"));
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;
	

	CurrentPawnSpeed = Pawn->GetVelocity().Size();

	

	//UE_LOG(LogTemp, Error, TEXT("speed : %f"), CurrentPawnSpeed);
	//auto Character = Cast<ACharacter>(Pawn);
}