/*
Steven Esposito
8/29/2020
*/

#include "ProjectileBase.h"
#include "AsteroidsRemake/Actors/ProjectileAsteroid.h"
#include "AsteroidsRemake/GameModes/AsteroidsGameModeBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "Particles/ParticleSystemComponent.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
			
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->ProjectileGravityScale = GravityScale;
	ProjectileMovement->Bounciness = BouncinessValue;
	ProjectileMovement->Friction = BounceFrictionValue;
	ProjectileMovement->bShouldBounce = bBounceOffSafeSurfaces;

	InitialLifeSpan = Lifespan;

	GameModeRef = Cast<AAsteroidsGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

void AProjectileBase::HandleDestruction(FVector RightVector)
{
	if (!GameModeRef)
	{
		UE_LOG(LogTemp, Error, TEXT("GameModeRef not set! for %s!"), *this->GetName());
		return;
	}

	GameModeRef->ActorDestroyed(this);
}

void AProjectileBase::DestroyProjectile()
{
	Destroy();
}