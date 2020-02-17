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

//ť�� �Žÿ� ���콺 Ŭ�������� ȣ��Ǵ� �Լ�
void ABulletComp_BOX::BoxCompOnClicked(class UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	bOnCursor = true;
}
//ť�� �Žÿ� ���콺 Ŭ�� ������ ȣ��Ǵ� �Լ�
void ABulletComp_BOX::BoxCompOnReleased(class UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	bOnCursor = false;
}

//���� ����׸� �ڽ��� ������Ʈ�� �㫉���� ȣ��Ǵ� �Լ�
void ABulletComp_BOX::OnOverlapBegin_LeftBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

//���� ����׸� �ڽ����� ������Ʈ ��ħ�� Ǯ���� ȣ��Ǵ� �Լ�
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

