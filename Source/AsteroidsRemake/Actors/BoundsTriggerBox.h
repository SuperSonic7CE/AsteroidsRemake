/*
Steven Esposito
8/29/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "BoundsTriggerBox.generated.h"

UCLASS()
class ASTEROIDSREMAKE_API ABoundsTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:

	ABoundsTriggerBox();

	UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

private:

	/** VARIABLES */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", meta = (AllowPrivateAccess = "true"))
		ABoundsTriggerBox* TargetTriggerBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", meta = (AllowPrivateAccess = "true"))
		int XOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", meta = (AllowPrivateAccess = "true"))
		int YOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", meta = (AllowPrivateAccess = "true"))
		bool TeleportOtherActor;
};
