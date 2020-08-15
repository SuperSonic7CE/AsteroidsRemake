// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketPawn.h"
//#include "Camera/CameraComponent.h"

ARocketPawn::ARocketPawn()
{
	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

void ARocketPawn::BeginPlay()
{
	Super::BeginPlay();

	//PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ARocketPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

	//UE_LOG(LogTemp, Warning, TEXT("Tick is working!"));
}

void ARocketPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARocketPawn::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &ARocketPawn::CalculateRotateInput);
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARocketPawn::Fire);
}

void ARocketPawn::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void ARocketPawn::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void ARocketPawn::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void ARocketPawn::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

void ARocketPawn::DestroyPawn()
{
	Super::DestroyPawn();

	bIsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

bool ARocketPawn::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}