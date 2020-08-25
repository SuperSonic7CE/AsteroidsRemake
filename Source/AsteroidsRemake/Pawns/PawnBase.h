/*
Steven Esposito
8/25/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UBoxComponent;
//class UHealthComponent;
class AProjectileBase;
class AProjectilePlayerBullet;

UCLASS()
class ASTEROIDSREMAKE_API APawnBase : public APawn
{
	GENERATED_BODY()

private:

	AProjectileBase* TempPlayerBullet;
	TArray<AActor*> PlayerBulletActors;

protected:

	/** Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* HitBoxComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* SpawnPointComp;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		//UHealthComponent* HealthComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectiles", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> PlayerBulletClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectiles", meta = (AllowPrivateAccess = "true"))
		int PlayerBulletMaxCount = 4;

	/** Effects */
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* DeathSFX;

	UFUNCTION()
		void Fire();

public:
	// Sets default values for this pawn's properties
	APawnBase();

	void PawnDefeated();
	virtual void DestroyPawn();

};