/*
Steven Esposito
8/23/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoundsHitbox.generated.h"

class UBoxComponent;

UCLASS()
class ASTEROIDSREMAKE_API ABoundsHitbox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoundsHitbox();

private:

	/** COMPONENTS */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* TriggerHitBoxComp;

	/** VARIABLES */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", meta = (AllowPrivateAccess = "true"))
		ABoundsHitbox* TargetHitbox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", meta = (AllowPrivateAccess = "true"))
		int XOffset = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", meta = (AllowPrivateAccess = "true"))
		int YOffset = 0;

	/** FUNCTIONS */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
