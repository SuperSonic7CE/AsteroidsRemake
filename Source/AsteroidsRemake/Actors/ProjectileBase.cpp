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

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projecile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	ProjectileMesh->SetEnableGravity(false);
	
	/*RandomRotationVector = FVector(FMath::RandRange(-1, 1), FMath::RandRange(-1, 1), 0);
	
	if (bRandomInitialRotation)
	{
		ProjectileMovement->Velocity *= RandomRotationVector;
	}*/
	
	/*RandomRotationVector = FVector(FMath::RandRange(-1, 1), FMath::RandRange(-1, 1), 0);

	ProjectileMovement->Velocity = RandomRotationVector;*/

	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->ProjectileGravityScale = GravityScale;
	ProjectileMovement->Bounciness = BouncinessValue;
	ProjectileMovement->Friction = BounceFrictionValue;
	ProjectileMovement->bShouldBounce = bBounceOffSafeSurfaces;

	//ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	//ParticleTrail->SetupAttachment(RootComponent);

	InitialLifeSpan = Lifespan;
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

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Projectile hit!"));

	AActor* MyOwner = GetOwner();

	if (!MyOwner)
	{
		return;
	}

	if (OtherActor && OtherActor != this)
	{
		if (OtherActor != MyOwner && OtherActor->GetClass() != this->GetClass())
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
			//UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
			//UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
			//GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
			Destroy();
		}
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