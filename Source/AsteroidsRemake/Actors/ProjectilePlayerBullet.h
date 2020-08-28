/*
Steven Esposito
8/25/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectilePlayerBullet.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class ASTEROIDSREMAKE_API AProjectilePlayerBullet : public AProjectileBase
{
	GENERATED_BODY()
	
public:

	AProjectilePlayerBullet();

	UFUNCTION()
		void OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	//UFUNCTION()
	//	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* HitBoxComp;

	virtual void Tick(float DeltaSeconds) override;

	bool bDestroyBullet = false;

};
