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
	

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	CollisionComp->SetupAttachment(SceneComp);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sad"));

	////////////////////////////////// 작업중인 곳
	
	// static FName Bullets[] = {TEXT("test1"), TEXT("test2"), TEXT("test3")};
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeItem(TEXT("/Game/StarterContent/Shapes/Shape_Pipe_180"));
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeItem2(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Wedge_A.Shape_Wedge_A'"));
	// if(CubeItem2.Succeeded())
	// {
	// 	StaticMesh->SetStaticMesh(CubeItem2.Object);
	// }
	// if(CubeItem.Succeeded())
	// {
	// 	for(auto Bullet : Bullets)
	// 	{
	// 		UStaticMeshComponent* BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(*Bullet.ToString());
	// 		BulletMesh->SetStaticMesh(CubeItem.Object);
	// 		BulletMesh->SetupAttachment(CollisionComp);
	// 		BoxStaticMesh.Add(BulletMesh);
	// 	}
	// }

	/////////////////////////////////////////////
	
	SelectBulletSlot = 1;

	RotateVector1.X = 35.0f;
	RotateVector1.Y = 0.0f;
	RotateVector1.Z = 0.0f;


	RotateVector2.X = 35.0f;
	RotateVector2.Y = 0.0f;
	RotateVector2.Z = 0.0f;

	RotateVector3.X = 35.0f;
	RotateVector3.Y = 0.0f;
	RotateVector3.Z = 0.0f;

	InitialLifeSpan = 80.0f;


	
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeItem(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// for(int i = 0; i<100; ++i)
	// {
	// 	BoxStaticMesh[i] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("asd"));
	// 	BoxStaticMesh[i]->SetStaticMesh(CubeItem.Object);
	// }
	
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


		//총알 가속도
		RotateVector1.X = RotateVector1.X - (float)BoxTransform1.Num() - ((float)CylinderTransform1.Num() * 0.7f) - ((float)SphereTransform1.Num() * 0.5f);
		RotateVector2.X = RotateVector2.X - (float)BoxTransform2.Num() - ((float)CylinderTransform2.Num() * 0.7f) - ((float)SphereTransform2.Num() * 0.5f);
		RotateVector3.X = RotateVector3.X - (float)BoxTransform3.Num() - ((float)CylinderTransform3.Num() * 0.7f) - ((float)SphereTransform3.Num() * 0.5f);


		//Bullet 효과 적용
		BulletImpactSolt1 = GameInstance->BulletImpactSolt1;
		BulletImpactSolt2 = GameInstance->BulletImpactSolt2;
		BulletImpactSolt3 = GameInstance->BulletImpactSolt3;
	}
}



// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginOverlap);
	
	////////////////////////////////// 작업중인 곳
	//AddComponent(FName(TEXT("asd")), false, CollisionComp->GetComponentTransform(), BoxStaticMesh);
	//CreateComponent(BoxStaticMesh, CollisionComp->GetComponentLocation(), CollisionComp->GetComponentRotation());
	//BoxStaticMesh.Add(NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass()));
	//BoxStaticMesh[0]->SetStaticMesh(StaticMesh->GetStaticMesh());
	//BoxStaticMesh[0]->SetRelativeRotation(FRotator(45.0f, 45.0f,45.0f));
	////////////////////////////////// 작업중인 곳
	

	
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

	// FVector Test[100];
	// FVector temp = {0, 0, 0};
	// for (int i = 0; i < 100; ++i)
	// {
	// 	temp.Z += RotateVector1.X * 10;
	// 	temp.Y += RotateY1 * 10;
	// 	temp.Z += RotateZ1 * 10;
	//
	// 	Test[i].X = temp.X;
	// 	Test[i].Y = temp.Y;
	// 	Test[i].Z = temp.Z;
	// }
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

	
		//회전
		CollisionComp->AddLocalRotation(FRotator(RotateZ1 * 200.0f, RotateY1 * 200.0f, 0.0f));
	}

	else if (SelectBulletSlot == 2) {
		RotateVector2.Y += RotateY2;
		RotateVector2.Z += RotateZ2;

		FTransform tf;
		tf.SetLocation(RotateVector2);
		AddActorLocalTransform(tf, false);

		//회전
		CollisionComp->AddLocalRotation(FRotator(RotateZ2 * 200.0f, RotateY2 * 200.0f, 0.0f));
	}

	else if (SelectBulletSlot == 3) {
		RotateVector3.Y += RotateY3;
		RotateVector3.Z += RotateZ3;

		FTransform tf;
		tf.SetLocation(RotateVector3);
		AddActorLocalTransform(tf, false);

		//회전
		CollisionComp->AddLocalRotation(FRotator(RotateZ3 * 200.0f, RotateY3 * 200.0f, 0.0f));
	}
}



void AProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	OverlappedComponent->DestroyComponent();
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAAAAAAAAAAAAAAAAAAAA"));
}


void AProjectile::CreateComponent(UStaticMeshComponent* CompClass, const FVector& Location, const FRotator& Rotation)
{
	FName YourObjectName("Hiiii");

	//CompClass can be a BP
	UStaticMeshComponent* NewComp = NewObject<UStaticMeshComponent>();
	if(!NewComp) 
	{
		return;
	}
	//~~~~~~~~~~~~~

	NewComp->RegisterComponent();        //You must ConstructObject with a valid Outer that has world, see above
	NewComp->SetStaticMesh(StaticMesh->GetStaticMesh());
	NewComp->SetWorldLocation(Location); 
	NewComp->SetWorldRotation(Rotation); 
	NewComp->SetupAttachment(CollisionComp); 
	//could use different than Root Comp
}




