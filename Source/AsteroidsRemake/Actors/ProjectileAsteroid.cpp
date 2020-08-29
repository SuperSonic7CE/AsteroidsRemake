/*
Steven Esposito
8/29/2020
*/


#include "ProjectileAsteroid.h"
#include "AsteroidsRemake/GameModes/AsteroidsGameModeBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectileAsteroid::AProjectileAsteroid()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Trigger"));
	RootComponent = TriggerSphereComp;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projecile Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetEnableGravity(false);

	TriggerSphereComp->OnComponentHit.AddDynamic(this, &AProjectileAsteroid::OnHit);	
}

void AProjectileAsteroid::BeginPlay()
{
	Super::BeginPlay();

	if (!GameModeRef)
	{
		UE_LOG(LogTemp, Error, TEXT("GameModeRef not set! for %s!"), *this->GetName());
		return;
	}

	if (TypeOfAsteroid == 1)
	{
		ScoreValue = GameModeRef->GetBigAsteroidPoints();
	}
	else if (TypeOfAsteroid == 2)
	{
		ScoreValue = GameModeRef->GetMediumAsteroidPoints();
	}
	else if (TypeOfAsteroid == 3)
	{
		ScoreValue = GameModeRef->GetSmallAsteroidPoints();
	}
	else		
	{
		UE_LOG(LogTemp, Error, TEXT("Score Value not set for %s!"), *this->GetName());
	}
}

void AProjectileAsteroid::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!bBounceOffSafeSurfaces)
	{
		HandleDestruction(OtherActor->GetActorRightVector());
	}
}

int AProjectileAsteroid::GetScoreValue()
{
	if (!ScoreValue)
	{
		UE_LOG(LogTemp, Error, TEXT("ScoreValue not set for %s!"), *this->GetName());
		ScoreValue = 0;
	}

	return ScoreValue;
}

void AProjectileAsteroid::HandleDestruction(FVector RightVector)
{
	if (SpawnProjectile)
	{
		RightVector = FVector(RightVector.X, RightVector.Y, 0.0f);

		FVector SpawnLocation = GetActorLocation() + RightVector * 25;
		FRotator SpawnRotation = RightVector.Rotation(); //FVector(FMath::FRandRange(0, 1), RandomY, 0).Rotation();
		TempSpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(SpawnProjectile, SpawnLocation, SpawnRotation);
		
		SpawnLocation = GetActorLocation() - RightVector * 25;
		SpawnRotation = (-RightVector).Rotation(); //FVector(FMath::FRandRange(-1, 0), RandomY, 0).Rotation();
		TempSpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(SpawnProjectile, SpawnLocation, SpawnRotation);
	}

	if (!GameModeRef)
	{
		UE_LOG(LogTemp, Error, TEXT("GameModeRef not set! for %s!"), *this->GetName());
		return;
	}

	float ExplosionSFXPitch;

	/* Small asteroids have the highest pitched explostion.
	   Medium asteroids have a lower pitched explostion.
	   Big asteroids have the lowest pitched explostion.
	*/
	if (ScoreValue == GameModeRef->GetSmallAsteroidPoints())
	{
		ExplosionSFXPitch = 1.0f;
	}
	else if (ScoreValue == GameModeRef->GetMediumAsteroidPoints())
	{
		ExplosionSFXPitch = 0.875f;
	}
	else if (ScoreValue == GameModeRef->GetBigAsteroidPoints())
	{
		ExplosionSFXPitch = 0.75f;
	}
		
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSFX, GetActorLocation(), 0.75f, FMath::FRandRange(ExplosionSFXPitch - 0.05f, ExplosionSFXPitch + 0.05f));
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	Super::HandleDestruction(RightVector);
}