/*
Steven Esposito
8/28/2020
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
	InitialThrusterZ = ThrusterMeshComp->GetRelativeLocation().X;
}

void ARocketPawn::BeginPlay()
{
	Super::BeginPlay();

	RespawnLocation = GetActorLocation();
	RespawnRotation = GetActorRotation();
}

void ARocketPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ThrusterMeshComp->IsVisible())
	{
		NewThrusterLocation = ThrusterMeshComp->GetRelativeLocation();

		NewThrusterLocation.Z = ThrusterLocationOffset + ThrusterAmplitudeOffset * FMath::Sin(ThrusterPeriodOffset * RunningTime);
		
		ThrusterMeshComp->SetRelativeLocation(NewThrusterLocation);
		RunningTime += DeltaTime;
	}

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
		FMath::Clamp(CurrentSpeed, 0.0f, MoveSpeed);
	}

	MoveDirection = PreviousForward * Value * CurrentSpeed * GetWorld()->DeltaTimeSeconds;
}

void ARocketPawn::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void ARocketPawn::Move()
{
	SetActorLocation(GetActorLocation() + MoveDirection);
}

void ARocketPawn::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

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