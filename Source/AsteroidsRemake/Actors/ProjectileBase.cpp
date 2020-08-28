/*
Steven Esposito
8/25/2020
*/


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Math/Vector.h"
#include "AsteroidsRemake/Actors/ProjectileAsteroid.h"
#include "AsteroidsRemake/GameModes/AsteroidsGameModeBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projecile Mesh"));
	//ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	//RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
			
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->ProjectileGravityScale = GravityScale;
	ProjectileMovement->Bounciness = BouncinessValue;
	ProjectileMovement->Friction = BounceFrictionValue;
	ProjectileMovement->bShouldBounce = bBounceOffSafeSurfaces;

	//ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	//ParticleTrail->SetupAttachment(RootComponent);

	InitialLifeSpan = Lifespan;

	GameModeRef = Cast<AAsteroidsGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	/*if (bRandomInitialRotation)
	{
		SetActorRotation(RandomRotationVector.Rotation());
	}	*/

	/*FVector TempVector = ProjectileMovement->Velocity;
	UE_LOG(LogTemp, Warning, TEXT("Velocity X: %f Y: %f Z: %f"), TempVector.X, TempVector.Y, TempVector.Z);

	ProjectileMovement->Velocity *= GetActorForwardVector();
	TempVector = ProjectileMovement->Velocity;*/
	//UE_LOG(LogTemp, Warning, TEXT("Velocity X: %f Y: %f Z: %f"), RandomRotationVector.X, RandomRotationVector.Y, RandomRotationVector.Z);

	//UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectileBase::HandleDestruction(FVector RightVector)
{
	if (GameModeRef)
	{
		GameModeRef->ActorDestroyed(this);
	}
}

void AProjectileBase::DestroyProjectile()
{
	Destroy();
}