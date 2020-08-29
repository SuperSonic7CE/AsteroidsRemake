/*
Steven Esposito
8/29/2020
*/

#include "BoundsTriggerBox.h"

ABoundsTriggerBox::ABoundsTriggerBox()
{
	PrimaryActorTick.bCanEverTick = false;

	OnActorBeginOverlap.AddDynamic(this, &ABoundsTriggerBox::OnOverlapBegin);
}

void ABoundsTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!TargetTriggerBox)
	{
		UE_LOG(LogTemp, Error, TEXT("TargetTriggerBox not set! for %s!"), *this->GetName());
		return;
	}

	if (OtherActor && OtherActor != this && TeleportOtherActor)
	{
		if (XOffset != 0)
		{
			OtherActor->SetActorLocation(FVector(TargetTriggerBox->GetActorLocation().X + 
				(TargetTriggerBox->GetComponentsBoundingBox().GetExtent().X + OtherActor->GetComponentsBoundingBox().GetSize().X) * XOffset,
				OtherActor->GetActorLocation().Y, OtherActor->GetActorLocation().Z));
		}
		else if (YOffset != 0)
		{
			OtherActor->SetActorLocation(FVector(OtherActor->GetActorLocation().X, TargetTriggerBox->GetActorLocation().Y +
				(TargetTriggerBox->GetComponentsBoundingBox().GetExtent().Y + OtherActor->GetComponentsBoundingBox().GetSize().Y) * YOffset,
				OtherActor->GetActorLocation().Z));
		}
	}
}