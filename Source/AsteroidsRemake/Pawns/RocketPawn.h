/*
Steven Esposito
8/21/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "RocketPawn.generated.h"


//class UCameraComponent;

/**
 * 
 */
UCLASS()
class ASTEROIDSREMAKE_API ARocketPawn : public APawnBase
{
	GENERATED_BODY()
	
public:

	ARocketPawn();

	void RevivePlayer();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void DestroyPawn() override;


private:

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	//	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float FrictionAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float RotateSpeed;

	float CurrentSpeed;

	FVector MoveDirection;
	FVector PreviousForward;
	FQuat RotationDirection;

	FVector SpawnLocation;
	FRotator SpawnRotation;

	//APlayerController* PlayerControllerRef;
	//FHitResult TraceHitResult;

	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);

	void Move();
	void Rotate();

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void FadeOut();
	UFUNCTION(BlueprintImplementableEvent)
		void FadeIn();

	void TurnOffInvincibility();

	int InvincibilityDelay = 2;
};