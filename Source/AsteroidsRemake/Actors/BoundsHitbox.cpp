/*
Steven Esposito
8/23/2020
*/


#include "BoundsHitbox.h"
#include "Components/BoxComponent.h"

// Sets default values
ABoundsHitbox::ABoundsHitbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	

	TriggerHitBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	TriggerHitBoxComp->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = TriggerHitBoxComp;

	TriggerHitBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABoundsHitbox::OnOverlapBegin);

	//UE_LOG(LogTemp, Warning, TEXT("BoundHitbox constructed. %f"), TriggerHitBoxComp->GetScaledBoxExtent().X);
	TArray<AActor*> OverlappingActors;

	TriggerHitBoxComp->GetOverlappingActors(OUT OverlappingActors);
	//UE_LOG(LogTemp, Warning, TEXT("%i"), OverlappingActors.Num());
	for (AActor* Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping with %s"), *Actor->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("%s is on the pressure plate!"), *Actor->GetName());
	}
}

void ABoundsHitbox::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Hit!"), *OtherActor->GetName());

	if (OtherActor && OtherActor != this)
	{
		if (XOffset != 0)
		{
			OtherActor->SetActorLocation(FVector(OtherActor->GetActorLocation().X + (TargetHitbox->TriggerHitBoxComp->GetScaledBoxExtent().X * XOffset),
				TargetHitbox->GetActorLocation().Y, OtherActor->GetActorLocation().Z));
		}
		else if (YOffset != 0)
		{			
			OtherActor->SetActorLocation(FVector(TargetHitbox->GetActorLocation().X, OtherActor->GetActorLocation().Y + (TargetHitbox->TriggerHitBoxComp->GetScaledBoxExtent().Y * YOffset),
				OtherActor->GetActorLocation().Z));
		}
	}
}

void ABoundsHitbox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("BoundHitbox hit!"));
}