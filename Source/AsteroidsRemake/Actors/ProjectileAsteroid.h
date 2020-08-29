/*
Steven Esposito
8/29/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileAsteroid.generated.h"

class USphereComponent;

UCLASS()
class ASTEROIDSREMAKE_API AProjectileAsteroid : public AProjectileBase
{
	GENERATED_BODY()
	

public:

	AProjectileAsteroid();

	int GetScoreValue();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int TypeOfAsteroid;

	virtual void HandleDestruction(FVector RightVector) override;


private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Projectile", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> SpawnProjectile;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USphereComponent* TriggerSphereComp;

	AProjectileBase* TempSpawnedProjectile;


protected:

	/** Functions */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void BeginPlay() override;

	/** Effects */
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* ExplosionSFX;
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathParticle;

	int ScoreValue;
};
