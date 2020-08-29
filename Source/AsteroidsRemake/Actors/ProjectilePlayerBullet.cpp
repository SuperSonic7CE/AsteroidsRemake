/*
Steven Esposito
8/29/2020
*/


#include "ProjectilePlayerBullet.h"
#include "Components/BoxComponent.h"
#include "ProjectileAsteroid.h"

AProjectilePlayerBullet::AProjectilePlayerBullet()
{	
	HitBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = HitBoxComp;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projecile Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetEnableGravity(false);

	HitBoxComp->SetGenerateOverlapEvents(true);
	OnActorBeginOverlap.AddDynamic(this, &AProjectilePlayerBullet::OnActorOverlapBegin);

	bDestroyBullet = false;
}

void AProjectilePlayerBullet::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bDestroyBullet)
	{
		Destroy();
	}
}

void AProjectilePlayerBullet::OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (Cast<AProjectileAsteroid>(OtherActor))
		{
			SetActorEnableCollision(false);
			Cast<AProjectileAsteroid>(OtherActor)->HandleDestruction(GetActorRightVector());
			
			HandleDestruction(GetActorRightVector());
			bDestroyBullet = true;
		}
	}
}