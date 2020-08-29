/*
Steven Esposito
8/21/2020
*/

#include "RocketPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
//#include "Camera/CameraComponent.h"

ARocketPawn::ARocketPawn()
{
	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	MoveSpeed = 200.0f;
	FrictionAmount = 0.5f;
	RotateSpeed = 50.0f;
	CurrentSpeed = 0.0f;

	ThrusterMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thruster Mesh"));
	ThrusterMeshComp->SetupAttachment(MeshComp);
	ThrusterMeshComp->SetVisibility(false);
	InitialThrusterZ = ThrusterMeshComp->GetRelativeLocation().X;
	ThrusterLocationOffset = -65.0f;
	ThrusterAmplitudeOffset = 10.0f;
	ThrusterPeriodOffset = 10.0f;
	RunningTime = 0.0f;
}

void ARocketPawn::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();
	SpawnRotation = GetActorRotation();

	//PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ARocketPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ThrusterMeshComp->IsVisible())
	{
		FVector NewThrusterLocation = ThrusterMeshComp->GetRelativeLocation();

		//NewLocation.Z += FMath::Sin(RunningTime);
		NewThrusterLocation.Z = ThrusterLocationOffset + ThrusterAmplitudeOffset * FMath::Sin(ThrusterPeriodOffset * RunningTime);
		
		ThrusterMeshComp->SetRelativeLocation(NewThrusterLocation);
		RunningTime += DeltaTime;
	}

	Rotate();
	Move();

	//UE_LOG(LogTemp, Warning, TEXT("Forward Vector: %f, %f, %f"), GetActorForwardVector().X, GetActorForwardVector().Y, GetActorForwardVector().Z);
}

void ARocketPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARocketPawn::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &ARocketPawn::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARocketPawn::Fire);
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARocketPawn::Fire);
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

	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), MoveDirection.X, MoveDirection.Y, MoveDirection.Z);
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
	//MeshComp->AddForce(MoveDirection * MoveSpeed * MeshComp->GetMass());
}

void ARocketPawn::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
	/*FVector TempVector = GetActorForwardVector();
	UE_LOG(LogTemp, Warning, TEXT("Forward Vector X: %f Y: %f Z: %f"), TempVector.X, TempVector.Y, TempVector.Z);*/
	//MeshComp->AddTorque(FVector(0.0f, 0.0f, 1.0f) * RotateSpeed * MeshComp->GetMass());
}

void ARocketPawn::DestroyPawn()
{
	SetActorEnableCollision(false);
	//HitBoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetIsPlayerAlive(false);

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	FadeOut();

	//Super::DestroyPawn();
}

void ARocketPawn::RevivePlayer()
{
	FTimerHandle PlayerInvincibilityHandle;
	FTimerDelegate PlayerInvincibilityDelegate = FTimerDelegate::CreateUObject(this, &ARocketPawn::TurnOffInvincibility);

	GetWorld()->GetTimerManager().SetTimer(PlayerInvincibilityHandle, PlayerInvincibilityDelegate, InvincibilityDelay, false);

	SetActorLocation(SpawnLocation);
	SetActorRotation(SpawnRotation);
	
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	SetIsPlayerAlive(true);
}

void ARocketPawn::TurnOffInvincibility()
{
	FadeIn();
	SetActorEnableCollision(true);	
	//HitBoxComp->SetCollisionEnabled(ECollisionEnabled:: );
}