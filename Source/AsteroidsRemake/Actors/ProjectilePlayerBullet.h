/*
Steven Esposito
8/29/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectilePlayerBullet.generated.h"

class UBoxComponent;

UCLASS()
class ASTEROIDSREMAKE_API AProjectilePlayerBullet : public AProjectileBase
{
	GENERATED_BODY()
	
public:

	AProjectilePlayerBullet();

	UFUNCTION()
		void OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* HitBoxComp;

	virtual void Tick(float DeltaSeconds) override;

	bool bDestroyBullet;

};
