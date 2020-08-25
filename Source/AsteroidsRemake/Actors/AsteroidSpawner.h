/*
Steven Esposito
8/25/2020
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
		bool bSpawnOnBeginPlay = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner", meta = (AllowPrivateAccess = "true"))
		bool bRandomInitialRotation = true;

	UFUNCTION()
		void SpawnProjectile();
	UFUNCTION()
		TSubclassOf<AProjectileBase> GetProjectile();
	UFUNCTION()
		void SetProjectile(TSubclassOf<AProjectileBase> NewProjectile);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AProjectileBase* TempProjectile;
	FRotator SpawnRotation;
};
