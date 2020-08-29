/*
Steven Esposito
8/23/2020
*/

#include "BoundsTriggerBox.h"

ABoundsTriggerBox::ABoundsTriggerBox()
{
	OnActorEndOverlap.AddDynamic(this, &ABoundsTriggerBox::OnOverlapEnd);
}

void ABoundsTriggerBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("Bounds X: %f"), GetComponentsBoundingBox().GetExtent().X);
	//UE_LOG(LogTemp, Warning, TEXT("Size X: %f"), GetComponentsBoundingBox().GetSize().X);
	//UE_LOG(LogTemp, Warning, TEXT("Center X: %f"), GetComponentsBoundingBox().GetCenter().X);
	//UE_LOG(LogTemp, Warning, TEXT("Overlapped with %s"), *OtherActor->GetName());

	if (!TargetTriggerBox)
	{
		UE_LOG(LogTemp, Error, TEXT("TargetTriggerBox not set!"));
		return;
	}

	if (OtherActor && OtherActor != this && TeleportOtherActor)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Overlapped with %s"), *OtherActor->GetName());

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