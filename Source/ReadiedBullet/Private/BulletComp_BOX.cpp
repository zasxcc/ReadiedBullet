// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "BulletComp_BOX.h"

// Sets default values
ABulletComp_BOX::ABulletComp_BOX()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	LeftBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	RightBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	UpBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Up"));
	DownBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Down"));
	FrontBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front"));
	BackBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Back"));

	LeftBox->OnComponentBeginOverlap.AddDynamic(this, &ABulletComp_BOX::OnOverlapBegin_LeftBox);
	LeftBox->OnComponentEndOverlap.AddDynamic(this, &ABulletComp_BOX::OnOverlapEnd_LeftBox);

	BoxComp->OnClicked.AddDynamic(this, &ABulletComp_BOX::BoxCompOnClicked);
	BoxComp->OnReleased.AddDynamic(this, &ABulletComp_BOX::BoxCompOnReleased);
}

// Called when the game starts or when spawned
void ABulletComp_BOX::BeginPlay()
{
	Super::BeginPlay();

	bOnCursor = false;

	LeftBox->SetCollisionObjectType(ECC_GameTraceChannel1);
}

//큐브 매시에 마우스 클릭했을떄 호출되는 함수
void ABulletComp_BOX::BoxCompOnClicked(class UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	bOnCursor = true;
}
//큐브 매시에 마우스 클릭 땟을때 호출되는 함수
void ABulletComp_BOX::BoxCompOnReleased(class UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	bOnCursor = false;
}

//왼쪽 노란네모 박스에 컴포넌트가 겹쳣을때 호출되는 함수
void ABulletComp_BOX::OnOverlapBegin_LeftBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

//왼쪽 노란네모 박스에서 컴포넌트 겹침이 풀릴때 호출되는 함수
void ABulletComp_BOX::OnOverlapEnd_LeftBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}



// Called every frame
void ABulletComp_BOX::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bOnCursor == true)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(BoxComp, 0);;

		PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

		NewWorldLocation.X = HitResult.Location.X;
		NewWorldLocation.Y = HitResult.Location.Y;
		NewWorldLocation.Z = 100.0f;

		BoxComp->SetWorldLocation(NewWorldLocation, false);
	}

}

