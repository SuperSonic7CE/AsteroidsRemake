/*
Steven Esposito
8/29/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "AsteroidSpawner.generated.h"

class AProjectileBase;

UCLASS()
class ASTEROIDSREMAKE_API AAsteroidSpawner : public ATargetPoint
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner", meta = (AllowPrivateAccess = "true"))
		bool bSpawnOnBeginPlay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner", meta = (AllowPrivateAccess = "true"))
		bool bRandomInitialRotation;

	UFUNCTION()
		void SpawnProjectile();
	UFUNCTION()
		TSubclassOf<AProjectileBase> GetProjectile();
	UFUNCTION()
		void SetProjectile(TSubclassOf<AProjectileBase> NewProjectile);


protected:
	virtual void BeginPlay() override;

	AProjectileBase* TempProjectile;
	FRotator SpawnRotation;
};
