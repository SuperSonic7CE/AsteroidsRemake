/*
Steven Esposito
8/29/2020
*/

#include "RocketPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"

ARocketPawn::ARocketPawn()
{
	MoveSpeed = 200.0f;
	FrictionAmount = 0.5f;
	RotateSpeed = 50.0f;
	CurrentSpeed = 0.0f;
	InvincibilityDelay = 2.0f;
	ThrusterLocationOffset = -65.0f;
	ThrusterAmplitudeOffset = 10.0f;
	ThrusterPeriodOffset = 10.0f;
	RunningTime = 0.0f;

	ThrusterMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thruster Mesh"));
	ThrusterMeshComp->SetupAttachment(MeshComp);
	ThrusterMeshComp->SetVisibility(false);
}

void ARocketPawn::BeginPlay()
{
	Super::BeginPlay();

	RespawnLocation = GetActorLocation();
	RespawnRotation = GetActorRotation();
	InitialThrusterZ = ThrusterMeshComp->GetRelativeLocation().X;
}

void ARocketPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	MoveThruster(DeltaSeconds);
	Rotate();
	Move();
}

void ARocketPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARocketPawn::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &ARocketPawn::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARocketPawn::Fire);
}

#pragma region Movement and Rotation

void ARocketPawn::CalculateMoveInput(float Value)
{
	// Give player rocket momentum if MoveForward input is not pressed and CurrentSpeed is not depleted fully by FrictionAmount 
	if (Value >= 1.0f)
	{
		ThrusterMeshComp->SetVisibility(true);
		CurrentSpeed = MoveSpeed;
		PreviousForward = GetActorForwardVector();
	}
	else if (CurrentSpeed > 0.0f)
	{
		ThrusterMeshComp->SetVisibility(false);
		CurrentSpeed -= FrictionAmount;
		Value = 1.0f;
		//FMath::Clamp(CurrentSpeed, 0.0f, MoveSpeed);

		if (CurrentSpeed < 0.0f)
		{
			CurrentSpeed = 0.0f;
		}
		else if (CurrentSpeed > MoveSpeed)
		{
			CurrentSpeed = MoveSpeed;
		}
	}

	MoveDirection = PreviousForward * Value * CurrentSpeed * GetWorld()->DeltaTimeSeconds;
}

void ARocketPawn::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

// Pulsate thruster up and down to create the illusion of fire.
void ARocketPawn::MoveThruster(float DeltaSeconds)
{
	if (ThrusterMeshComp->IsVisible())
	{
		NewThrusterLocation = ThrusterMeshComp->GetRelativeLocation();

		NewThrusterLocation.Z = ThrusterLocationOffset + ThrusterAmplitudeOffset * FMath::Sin(ThrusterPeriodOffset * RunningTime);

		ThrusterMeshComp->SetRelativeLocation(NewThrusterLocation);
		RunningTime += DeltaSeconds;
	}
}

void ARocketPawn::Move()
{
	SetActorLocation(GetActorLocation() + MoveDirection);
}

void ARocketPawn::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

#pragma endregion

#pragma region Destruction and Respawning

void ARocketPawn::DestroyPawn()
{
	SetActorEnableCollision(false);
	SetIsPlayerAlive(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	FadeOut();
}

void ARocketPawn::RevivePlayer()
{
	FTimerHandle PlayerInvincibilityHandle;
	FTimerDelegate PlayerInvincibilityDelegate = FTimerDelegate::CreateUObject(this, &ARocketPawn::TurnOffInvincibility);

	GetWorld()->GetTimerManager().SetTimer(PlayerInvincibilityHandle, PlayerInvincibilityDelegate, InvincibilityDelay, false);

	SetActorLocation(RespawnLocation);
	SetActorRotation(RespawnRotation);
	
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	SetIsPlayerAlive(true);
}

void ARocketPawn::TurnOffInvincibility()
{
	FadeIn();
	SetActorEnableCollision(true);
}

#pragma endregion