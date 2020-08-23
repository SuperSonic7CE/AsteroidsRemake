/*
Steven Esposito
8/21/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UBoxComponent;
//class UHealthComponent;
class AProjectileBase;

UCLASS()
class ASTEROIDSREMAKE_API APawnBase : public APawn
{
	GENERATED_BODY()

private:

	AProjectileBase* TempProjectile;
	TArray<AActor*> ProjectileActors;

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
		TSubclassOf<AProjectileBase> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectiles", meta = (AllowPrivateAccess = "true"))
		int ProjectileMaxCount = 4;

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
