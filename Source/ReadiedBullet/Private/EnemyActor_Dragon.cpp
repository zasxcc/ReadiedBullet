
#include "EnemyActor_Dragon.h"

// Sets default values
AEnemyActor_Dragon::AEnemyActor_Dragon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));



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
