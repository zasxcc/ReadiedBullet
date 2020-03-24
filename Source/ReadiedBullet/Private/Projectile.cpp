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



	//BP 연결
	static ConstructorHelpers::FObjectFinder<UBlueprint> CubeItem(TEXT("/Game/Blueprints/BP_Cube"));

	if (CubeItem.Object)
	{
		CubeBlueprint = (UClass*)CubeItem.Object->GeneratedClass;
		
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> CylinerItem(TEXT("/Game/Blueprints/BP_Cylinder"));

	if (CylinerItem.Object)
	{
		CylinderBlueprint = (UClass*)CylinerItem.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> SphereItem(TEXT("/Game/Blueprints/BP_Sphere"));

	if (SphereItem.Object)
	{
		SphereBlueprint = (UClass*)SphereItem.Object->GeneratedClass;
	}

	RotateVector.X = 10.0f;
	RotateVector.Y = 0.0f;
	RotateVector.Z = 0.0f;

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
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	


	RotateVector.Y += RotateY;
	RotateVector.Z += RotateZ;
	
	FTransform tf;
	tf.SetLocation(RotateVector);

	AddActorLocalTransform(tf, false);

	
	CollisionComp->AddLocalRotation(FRotator(RotateZ*200.0f, RotateY * 200.0f, 0.0f));

}



// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	float rotateRatio = 0.05f;

	RotateX = (GameInstance->InstanceX * rotateRatio);
	RotateY = (GameInstance->InstanceY * rotateRatio);
	RotateZ = (GameInstance->InstanceZ * rotateRatio);
	

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
//	Destroy();
//}


