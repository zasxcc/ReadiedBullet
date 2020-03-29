// Fill out your copyright notice in the Description page of Project Settings.


#include "BarghestAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ABarghestAIController::HomePosKey(TEXT("HomePos"));
const FName ABarghestAIController::PatrolPosKey(TEXT("PatrolPos"));

ABarghestAIController::ABarghestAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_Barghest.BB_Barghest"));

	if (BBObject.Succeeded())
		BBAsset = BBObject.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_Barghest.BT_Barghest"));

	if (BTObject.Succeeded())
		BTAsset = BTObject.Object;
}

void ABarghestAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
	}
}