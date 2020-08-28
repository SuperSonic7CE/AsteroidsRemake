/*
Steven Esposito
8/25/2020
*/


#include "ProjectileAsteroid.h"
#include "Components/SphereComponent.h"

AProjectileAsteroid::AProjectileAsteroid()
{
	TriggerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Trigger"));
	RootComponent = TriggerSphereComp;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projecile Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetEnableGravity(false);
	
	TriggerSphereComp->OnComponentHit.AddDynamic(this, &AProjectileAsteroid::OnHit);
}

void AProjectileAsteroid::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//FVector TempLocation = GetActorLocation();

	//SetActorLocation(FVector(TempLocation.X, TempLocation.Y, 100.0f));

	//UE_LOG(LogTemp, Warning, TEXT("Projectile hit!"));

	//AActor* MyOwner = GetOwner();

	//if (!MyOwner)
	//{
		//return;
	//}

	//if (OtherActor && OtherActor != this)
	//{
	//	//if (OtherActor != MyOwner) //&& (!Cast<AProjectileAsteroid>(OtherActor) || !Cast<AProjectileAsteroid>(this)))
	//	if (!Cast<AProjectileAsteroid>(OtherActor) || !Cast<AProjectileAsteroid>(this))
	//	{
	//		//UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
	//		//UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
	//		//UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	//		//GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);

	//		ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//		DestroyProjectile(OtherActor->GetActorRightVector());
	//	}
	//	//else
	//	//{
	//	//	FVector TempVector = GetActorForwardVector();
	//	//	UE_LOG(LogTemp, Warning, TEXT("Forward Vector X: %f Y: %f Z: %f"), TempVector.X, TempVector.Y, TempVector.Z);
	//	//	
	//	//	TempVector = TempVector.MirrorByVector(Hit.ImpactNormal);
	//	//	UE_LOG(LogTemp, Warning, TEXT("Mirrored Forward Vector X: %f Y: %f Z: %f"), TempVector.X, TempVector.Y, TempVector.Z);
	//	//	//SetActorRotation(TempVector.Rotation());
	//	//	//SetActorLocation(FVector(GetActorForwardVector().X, GetActorForwardVector().Y + 1, GetActorForwardVector().Z));
	//	//	//UE_LOG(LogTmep, Warning, TEXT("Speed: %f"), ProjectileMovement->Set)
	//	//}		
	//}
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

		//float RandomX = FMath::FRandRange(-1, 1);
		//float RandomY = 0; //FMath::FRandRange(-1, 1);

		//TriggerSphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FVector SpawnLocation = GetActorLocation() + RightVector * 25;
		//SpawnLocation = FVector(SpawnLocation.X, SpawnLocation.Y, 100.0f);
		FRotator SpawnRotation = RightVector.Rotation(); //FVector(FMath::FRandRange(0, 1), RandomY, 0).Rotation();

		TempSpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(SpawnProjectile, SpawnLocation, SpawnRotation);
		//TempSpawnedProjectile->SetOwner(this);

		SpawnLocation = GetActorLocation() - RightVector * 25;
		//SpawnLocation = FVector(SpawnLocation.X, SpawnLocation.Y, 100.0f);
		SpawnRotation = (-RightVector).Rotation(); //FVector(FMath::FRandRange(-1, 0), RandomY, 0).Rotation();

		TempSpawnedProjectile = GetWorld()->SpawnActor<AProjectileBase>(SpawnProjectile, SpawnLocation, SpawnRotation);
		//TempSpawnedProjectile->SetOwner(this);
	}	

	Super::HandleDestruction(RightVector);
}