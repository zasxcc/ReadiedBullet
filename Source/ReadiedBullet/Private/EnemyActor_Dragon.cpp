
#include "EnemyActor_Dragon.h"

// Sets default values
AEnemyActor_Dragon::AEnemyActor_Dragon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);

	Capsule->SetCapsuleHalfHeight(150.f);
	Capsule->SetCapsuleRadius(100.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DRAGON_BODY(TEXT("/Game/QuadrapedCreatures/MountainDragon/Meshes/SK_MOUNTAIN_DRAGON.SK_MOUNTAIN_DRAGON"));
	if (DRAGON_BODY.Succeeded())
	{
		Mesh->SetSkeletalMesh(DRAGON_BODY.Object);
	}

	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> DRAGON_ANIM(TEXT("/Game/QuadrapedCreatures/Blueprints/DragonAnimBlueprint.DragonAnimBlueprint_C"));
	if (DRAGON_ANIM.Succeeded())
	{
		Mesh->SetAnimInstanceClass(DRAGON_ANIM.Class);
	}
}

// Called when the game starts or when spawned
void AEnemyActor_Dragon::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void AEnemyActor_Dragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
