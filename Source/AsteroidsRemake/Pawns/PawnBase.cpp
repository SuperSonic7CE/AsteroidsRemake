/*
Steven Esposito
8/21/2020
*/

#include "PawnBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = HitBoxComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

	SpawnPointComp = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPointComp->SetupAttachment(MeshComp);
}

void APawnBase::PawnDefeated()
{
	DestroyPawn();
}

void APawnBase::DestroyPawn()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSFX, GetActorLocation());
}