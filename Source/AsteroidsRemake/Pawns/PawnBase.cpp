/*
Steven Esposito
8/29/2020
*/

#include "PawnBase.h"
#include "AsteroidsRemake/Actors/ProjectilePlayerBullet.h"
#include "AsteroidsRemake/Actors/ProjectileAsteroid.h"
#include "AsteroidsRemake/GameModes/AsteroidsGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

APawnBase::APawnBase()
{
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

	bIsPlayerAlive = true;
};

void APawnBase::PawnDefeated()
{
	if (!GameModeRef)
	{
		UE_LOG(LogTemp, Error, TEXT("GameModeRef not set for %s!"), *this->GetName());
		return;		
	}
	
	GameModeRef->ActorDestroyed(this);

	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSFX, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
}

void APawnBase::DestroyPawn()
{
	Destroy();
}

void APawnBase::Fire()
{
	if (!bIsPlayerAlive)
	{
		return;
	}

	if (!PlayerBulletClass)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerBulletClass not set for %s!"), *this->GetName());
		return;
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProjectilePlayerBullet::StaticClass(), PlayerBulletActors);

	if (PlayerBulletActors.Num() < PlayerBulletMaxCount)
	{
		ProjectileSpawnLocation = SpawnPointComp->GetComponentLocation();
		ProjectileSpawnRotation = SpawnPointComp->GetComponentRotation();

		TempPlayerBullet = GetWorld()->SpawnActor<AProjectileBase>(PlayerBulletClass, ProjectileSpawnLocation, ProjectileSpawnRotation);
		TempPlayerBullet->SetOwner(this);
		UGameplayStatics::PlaySoundAtLocation(this, LaserSFX, ProjectileSpawnLocation);
	}
}

void APawnBase::OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<AProjectileAsteroid>(OtherActor))
	{
		PawnDefeated();
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