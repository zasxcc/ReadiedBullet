
#include "EnemyActor_Dragon.h"

// Sets default values
AEnemyActor_Dragon::AEnemyActor_Dragon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	//HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	//HPBarWidget->SetupAttachment(Mesh);

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


	//왜안댐? 시발진짜
	/*static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/UI/WBP_HPBar"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(200.0f, 80.0));
	}

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 500.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);*/


	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor_Dragon::OnOverlapBegin_Mesh);
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



void AEnemyActor_Dragon::OnOverlapBegin_Mesh(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//이건 왜 안댐? 시발
	UE_LOG(LogTemp, Warning, TEXT("asdasdsad"));
}