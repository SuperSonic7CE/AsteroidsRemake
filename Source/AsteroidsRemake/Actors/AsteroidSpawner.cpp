/*
Steven Esposito
8/25/2020
*/


#include "AsteroidSpawner.h"
#include "AsteroidsRemake/Actors/ProjectileBase.h"

void AAsteroidSpawner::BeginPlay()
{
	if (bSpawnOnBeginPlay)
	{
		SpawnProjectile();
	}
}

void AAsteroidSpawner::SpawnProjectile()
{
	if (bRandomInitialRotation)
	{
		SpawnRotation = FVector(FMath::FRandRange(-1, 1), FMath::FRandRange(-1, 1), 0).Rotation();
	}
	else
	{
		SpawnRotation = GetActorRotation();
	}

	TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, GetActorLocation(), SpawnRotation);
	TempProjectile->SetOwner(this);
}

TSubclassOf<AProjectileBase> AAsteroidSpawner::GetProjectile()
{
	return ProjectileClass;
}

void AAsteroidSpawner::SetProjectile(TSubclassOf<AProjectileBase> NewProjectile)
{
	ProjectileClass = NewProjectile;
}