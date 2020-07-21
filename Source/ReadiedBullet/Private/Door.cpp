// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
	leftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LDoor"));
	rightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RDoor"));
	BoxCom = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	RootComponent = Root;
	PrimaryActorTick.bCanEverTick = true;
	BoxCom->ComponentTags.Add(FName("Door"));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	BoxCom->OnComponentBeginOverlap.AddDynamic(this, &ADoor::BeginOverlap);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance->openDoor)
	{
		if (leftDoorAngle > -270.0f) {
			leftDoorAngle -= 2.0f;
			leftDoor->SetRelativeRotation(FRotator(0.0f, leftDoorAngle, 0.0f));
			UE_LOG(LogTemp, Warning, TEXT("%f"), leftDoorAngle);
		}

		if (rightDoor->GetRelativeRotation().Yaw < 90.0f)
		{
			rightDoorAngel += 2.0f;
			rightDoor->SetRelativeRotation(FRotator(0.0f, rightDoorAngel, 0.0f));
		}
	}
}

void ADoor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("DoorLog"));

}