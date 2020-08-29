/*
Steven Esposito
8/29/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "RocketPawn.generated.h"

UCLASS()
class ASTEROIDSREMAKE_API ARocketPawn : public APawnBase
{
	GENERATED_BODY()
	
public:

	ARocketPawn();

	void RevivePlayer();
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void DestroyPawn() override;


private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float FrictionAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float RotateSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ThrusterMeshComp;

	float CurrentSpeed;
	float InitialThrusterZ;
	float ThrusterLocationOffset;
	float ThrusterAmplitudeOffset;
	float ThrusterPeriodOffset;
	float RunningTime;
	float InvincibilityDelay;

	FVector MoveDirection;
	FVector PreviousForward;
	FQuat RotationDirection;
	FVector RespawnLocation;
	FRotator RespawnRotation;
	FVector NewThrusterLocation;

	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);
	void Move();
	void Rotate();
	void MoveThruster(float DeltaSeconds);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void FadeOut();
	UFUNCTION(BlueprintImplementableEvent)
		void FadeIn();

	void TurnOffInvincibility();
};