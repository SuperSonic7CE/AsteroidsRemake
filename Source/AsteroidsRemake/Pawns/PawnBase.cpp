/*
Steven Esposito
8/25/2020
*/

#include "PawnBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AsteroidsRemake/Actors/ProjectilePlayerBullet.h"
#include "AsteroidsRemake/Actors/ProjectileAsteroid.h"
#include "AsteroidsRemake/GameModes/AsteroidsGameModeBase.h"
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

	HitBoxComp->SetGenerateOverlapEvents(true);
	OnActorBeginOverlap.AddDynamic(this, &APawnBase::OnActorOverlapBegin);

	GameModeRef = Cast<AAsteroidsGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
};

void APawnBase::PawnDefeated()
{
	if (GameModeRef)
	{
		GameModeRef->ActorDestroyed(this);
	}

	
	//DestroyPawn();
}

void APawnBase::DestroyPawn()
{
	//UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	//UGameplayStatics::PlaySoundAtLocation(this, DeathSFX, GetActorLocation());

	Destroy();
}

void APawnBase::Fire()
{
	if (!bIsPlayerAlive)
	{
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("FIRE!"));

	if (PlayerBulletClass)
	{
		//TArray<AActor*> ProjectileActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProjectilePlayerBullet::StaticClass(), PlayerBulletActors);

		if (PlayerBulletActors.Num() < PlayerBulletMaxCount)
		{
			FVector SpawnLocation = SpawnPointComp->GetComponentLocation();
			FRotator SpawnRotation = SpawnPointComp->GetComponentRotation();

			TempPlayerBullet = GetWorld()->SpawnActor<AProjectileBase>(PlayerBulletClass, SpawnLocation, SpawnRotation);
			TempPlayerBullet->SetOwner(this);
		}
	}
}

void APawnBase::OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	//UE_LOG(LogTemp, Error, TEXT("%s overlapped with Rocket!"), *OtherActor->GetName());

	if (Cast<AProjectileAsteroid>(OtherActor))
	{
		PawnDefeated();
		//Destroy();
	}
}

bool APawnBase::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}

void APawnBase::SetIsPlayerAlive(bool IsAlive)
{
	bIsPlayerAlive = IsAlive;
}