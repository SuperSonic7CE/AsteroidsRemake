/*
Steven Esposito
8/25/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileAsteroid.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDSREMAKE_API AProjectileAsteroid : public AProjectileBase
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Projectile", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> SpawnProjectile;

	AProjectileBase* TempSpawnedProjectile;

protected:

	virtual void DestroyProjectile(FVector RightVector) override;

};
