/*
Steven Esposito
8/29/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UBoxComponent;
class AProjectileBase;
class AProjectilePlayerBullet;
class AAsteroidsGameModeBase;

UCLASS()
class ASTEROIDSREMAKE_API APawnBase : public APawn
{
	GENERATED_BODY()


private:

	AProjectileBase* TempPlayerBullet;
	TArray<AActor*> PlayerBulletActors;
	AAsteroidsGameModeBase* GameModeRef;


protected:

	/** Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* HitBoxComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* SpawnPointComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectiles", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> PlayerBulletClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectiles", meta = (AllowPrivateAccess = "true"))
		int PlayerBulletMaxCount;

	/** Effects */
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* ExplosionSFX;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* LaserSFX;

	/** Functions */
	UFUNCTION()
		void Fire();

	FVector ProjectileSpawnLocation;
	FRotator ProjectileSpawnRotation;


public:

	APawnBase();

	UFUNCTION()
		void OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	void PawnDefeated();
	virtual void DestroyPawn();
	void SetIsPlayerAlive(bool IsAlive);
	bool GetIsPlayerAlive();
	
	bool bIsPlayerAlive;
};