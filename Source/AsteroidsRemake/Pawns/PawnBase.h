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

UCLASS()
class ASTEROIDSREMAKE_API APawnBase : public APawn
{
	GENERATED_BODY()

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

	/** Effects */
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* DeathSFX;		

public:
	// Sets default values for this pawn's properties
	APawnBase();

	void PawnDefeated();
	virtual void DestroyPawn();

};
