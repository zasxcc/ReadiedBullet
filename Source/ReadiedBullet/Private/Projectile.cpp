// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Engine.h"

// Sets default values
AProjectile::AProjectile()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));

	RootComponent = SceneComp;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->SetCollisionProfileName("Projectile");
	//CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);	// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	CollisionComp->SetupAttachment(SceneComp);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));

	//BP 연결
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeItem(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));


	//StaticMesh->SetStaticMesh(CubeItem.Object);

	SelectBulletSlot = 1;

	RotateVector1.X = 25.0f;
	RotateVector1.Y = 0.0f;
	RotateVector1.Z = 0.0f;

	RotateVector2.X = 25.0f;
	RotateVector2.Y = 0.0f;
	RotateVector2.Z = 0.0f;

	RotateVector3.X = 25.0f;
	RotateVector3.Y = 0.0f;
	RotateVector3.Z = 0.0f;

	InitialLifeSpan = 80.0f;
}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance)
	{
		BoxTransform1 = GameInstance->InstanceBoxSlot1;
		CylinderTransform1 = GameInstance->InstanceCylinderSlot1;
		SphereTransform1 = GameInstance->InstanceSphereSlot1;

		BoxTransform2 = GameInstance->InstanceBoxSlot2;
		CylinderTransform2 = GameInstance->InstanceCylinderSlot2;
		SphereTransform2 = GameInstance->InstanceSphereSlot2;

		BoxTransform3 = GameInstance->InstanceBoxSlot3;
		CylinderTransform3 = GameInstance->InstanceCylinderSlot3;
		SphereTransform3 = GameInstance->InstanceSphereSlot3;

		SelectBulletSlot = GameInstance->SelectSlot;
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	if (SelectBulletSlot == 1) {
		RotateVector1.Y += RotateY1;
		RotateVector1.Z += RotateZ1;

		FTransform tf;
		tf.SetLocation(RotateVector1);
		AddActorLocalTransform(tf, false);
		CollisionComp->AddLocalRotation(FRotator(RotateZ1 * 200.0f, RotateY1 * 200.0f, 0.0f));
	}

	else if (SelectBulletSlot == 2) {
		RotateVector2.Y += RotateY2;
		RotateVector2.Z += RotateZ2;

		FTransform tf;
		tf.SetLocation(RotateVector2);
		AddActorLocalTransform(tf, false);
		CollisionComp->AddLocalRotation(FRotator(RotateZ2 * 200.0f, RotateY2 * 200.0f, 0.0f));
	}

	else if (SelectBulletSlot == 3) {
		RotateVector3.Y += RotateY3;
		RotateVector3.Z += RotateZ3;

		FTransform tf;
		tf.SetLocation(RotateVector3);
		AddActorLocalTransform(tf, false);
		CollisionComp->AddLocalRotation(FRotator(RotateZ3 * 200.0f, RotateY3 * 200.0f, 0.0f));
	}
	
}



// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	float rotateRatio = 0.05f;
	
	RotateX1 = (GameInstance->SaveSlot1_InstanceX * rotateRatio);
	RotateY1 = (GameInstance->SaveSlot1_InstanceY * rotateRatio);
	RotateZ1 = (GameInstance->SaveSlot1_InstanceZ * rotateRatio);
	
	RotateX2 = (GameInstance->SaveSlot2_InstanceX * rotateRatio);
	RotateY2 = (GameInstance->SaveSlot2_InstanceY * rotateRatio);
	RotateZ2 = (GameInstance->SaveSlot2_InstanceZ * rotateRatio);

	RotateX3 = (GameInstance->SaveSlot3_InstanceX * rotateRatio);
	RotateY3 = (GameInstance->SaveSlot3_InstanceY * rotateRatio);
	RotateZ3 = (GameInstance->SaveSlot3_InstanceZ * rotateRatio);

	
}


//void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	// Only add impulse and destroy projectile if we hit a physics
//	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
//	{
//		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
//	}
//
//	//무언가에 닿았을때 노이즈를 낸다.
//	MakeNoise(1.0f, Instigator);
//
//
//	Destroy();
//}


