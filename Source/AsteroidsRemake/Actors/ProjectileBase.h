/*
Steven Esposito
8/25/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class AAsteroidsGameModeBase;

UCLASS()
class ASTEROIDSREMAKE_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	virtual void HandleDestruction(FVector RightVector);
	virtual void DestroyProjectile();

	AAsteroidsGameModeBase* GameModeRef;

protected:
	/** COMPONENTS */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ProjectileMesh;
	//UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	//	UClass* PointerToDamageType;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		//UParticleSystemComponent* ParticleTrail;

	/** VARIABLES */
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		float Damage = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		float Lifespan = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MovementSpeed = 1300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float GravityScale = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float BouncinessValue = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float BounceFrictionValue = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		bool bBounceOffSafeSurfaces = true;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		bool bRandomInitialRotation = true;*/
	//UPROPERTY(EditAnywhere, Category = "Effects")
		//UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* LaunchSound;
	//UPROPERTY(EditAnywhere, Category = "Effects")
		//TSubclassOf<UCameraShake> HitShake;
		
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//FVector RandomRotationVector;
};
