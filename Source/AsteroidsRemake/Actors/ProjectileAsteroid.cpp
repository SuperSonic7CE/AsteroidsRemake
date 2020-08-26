/*
Steven Esposito
8/25/2020
*/


#include "ProjectileAsteroid.h"

void AProjectileAsteroid::DestroyProjectile(FVector RightVector)
{
	if (SpawnProjectile)
	{
		//RightVector = FVector(RightVector.X, RightVector.Y, 0);

		//float RandomX = FMath::FRandRange(-1, 1);
		//float RandomY = 0; //FMath::FRandRange(-1, 1);

		FVector SpawnLocation = GetActorLocation() + RightVector * 50;
		FRotator SpawnRotation = RightVector.Rotation(); //FVector(FMath::FRandRange(0, 1), RandomY, 0).Rotation();

		TempSpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(SpawnProjectile, SpawnLocation, SpawnRotation);
		TempSpawnedProjectile->SetOwner(this);

		SpawnLocation = GetActorLocation() - RightVector * 50;
		SpawnRotation = (-RightVector).Rotation(); //FVector(FMath::FRandRange(-1, 0), RandomY, 0).Rotation();

		TempSpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(SpawnProjectile, SpawnLocation, SpawnRotation);
		TempSpawnedProjectile->SetOwner(this);
	}	

	Super::DestroyProjectile(RightVector);
}