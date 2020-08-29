/*
Steven Esposito
8/25/2020
*/


#include "ProjectilePlayerBullet.h"
#include "Components/BoxComponent.h"
#include "ProjectileAsteroid.h"

AProjectilePlayerBullet::AProjectilePlayerBullet()
{
	/*if (!this)
	{
		return;
	}*/
	
	HitBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = HitBoxComp;
	//HitBoxComp->SetupAttachment(RootComponent);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projecile Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetEnableGravity(false);

	HitBoxComp->SetGenerateOverlapEvents(true);
	OnActorBeginOverlap.AddDynamic(this, &AProjectilePlayerBullet::OnActorOverlapBegin);
	//HitBoxComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectilePlayerBullet::OnOverlapBegin);
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
	/*if (!this)
	{
		return;
	}*/

	//UE_LOG(LogTemp, Warning, TEXT("%s overlapped with Player Bullet!"), *OtherActor->GetName());

	//UE_LOG(LogTemp, Warning, TEXT("Projectile hit!"));

	/*AActor* MyOwner = GetOwner();

	if (!MyOwner)
	{
		return;
	}*/

	if (OtherActor && OtherActor != this)
	{
		/*if (OtherActor == MyOwner)
		{
			UE_LOG(LogTemp, Error, TEXT("Ignoring Owner"));
			
		}*/

		if (Cast<AProjectileAsteroid>(OtherActor))
		{
			HitBoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Cast<AProjectileAsteroid>(OtherActor)->HandleDestruction(GetActorRightVector());
			
			HandleDestruction(GetActorRightVector());
			bDestroyBullet = true;
			//Destroy();
		}		

		//if (OtherActor != MyOwner) //&& (!Cast<AProjectileAsteroid>(OtherActor) || !Cast<AProjectileAsteroid>(this)))
		//if (!Cast<AProjectileAsteroid>(OtherActor) || !Cast<AProjectileAsteroid>(this))
		//{
			//UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
			//UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
			//UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
			//GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);

		//	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		//	DestroyProjectile(OtherActor->GetActorRightVector());
		//}
		//else
		//{
		//	FVector TempVector = GetActorForwardVector();
		//	UE_LOG(LogTemp, Warning, TEXT("Forward Vector X: %f Y: %f Z: %f"), TempVector.X, TempVector.Y, TempVector.Z);
		//	
		//	TempVector = TempVector.MirrorByVector(Hit.ImpactNormal);
		//	UE_LOG(LogTemp, Warning, TEXT("Mirrored Forward Vector X: %f Y: %f Z: %f"), TempVector.X, TempVector.Y, TempVector.Z);
		//	//SetActorRotation(TempVector.Rotation());
		//	//SetActorLocation(FVector(GetActorForwardVector().X, GetActorForwardVector().Y + 1, GetActorForwardVector().Z));
		//	//UE_LOG(LogTmep, Warning, TEXT("Speed: %f"), ProjectileMovement->Set)
		//}		
	}
}

//void AProjectilePlayerBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	UE_LOG(LogTemp, Error, TEXT("%s overlapped with Player Bullet!"), *OtherActor->GetName());
//}