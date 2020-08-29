// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidsGameModeBase.h"
#include "AsteroidsRemake/Actors/ProjectileAsteroid.h"
#include "AsteroidsRemake/Pawns/RocketPawn.h"
#include "Kismet/GameplayStatics.h"

void AAsteroidsGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    //PrimaryActorTick.bCanEverTick = true;

    UGameplayStatics::PlaySound2D(this, BackgroundAudio);
    HandleGameStart();
}

//void AAsteroidsGameModeBase::Tick(float DeltaSeconds)
//{
//    Super::Tick(DeltaSeconds);
//
//    UE_LOG(LogTemp, Error, TEXT("Tick is working."));
//
//    if (ScoreValue < TotalScore)
//    {
//        SetScoreDisplay(++ScoreValue);
//    }
//    else if (ScoreValue > TotalScore)
//    {
//        ScoreValue = TotalScore;
//        SetScoreDisplay(ScoreValue);
//    }
//}

void AAsteroidsGameModeBase::ActorDestroyed(AActor* DestroyedActor)
{
    //UE_LOG(LogTemp, Warning, TEXT("A pawn died."));
    //UE_LOG(LogTemp, Warning, TEXT("%s"), *DestroyedActor->GetName());
    //UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerRocket->GetName());

    if (DestroyedActor == PlayerRocket)
    {
        PlayerRocket->DestroyPawn();
                
        SetLivesDisplay(--PlayerLives);
        TotalScore -= 1000;
        ScoreValue = TotalScore;
        SetScoreDisplay(ScoreValue);

        if (PlayerLives <= 0)
        {
            HandleGameOver(false);
        }
        else
        {
            FTimerHandle PlayerReviveHandle;
            FTimerDelegate PlayerReviveDelegate = FTimerDelegate::CreateUObject(PlayerRocket, &ARocketPawn::RevivePlayer);

            GetWorld()->GetTimerManager().SetTimer(PlayerReviveHandle, PlayerReviveDelegate, ReviveDelay, false);
        }

        /*if (RocketPlayerControllerRef)
        {
            RocketPlayerControllerRef->SetPlayerEnabledState(false);
        }*/
    }
    else if (AProjectileAsteroid* DestroyedAsteroid = Cast<AProjectileAsteroid>(DestroyedActor))
    {
        TotalScore += DestroyedAsteroid->GetScoreValue();
        ScoreValue = TotalScore;
        SetScoreDisplay(ScoreValue);
        DestroyedAsteroid->DestroyProjectile();

        if (--TargetAsteroids == 0)
        {
            HandleGameOver(true);
        }
    }

    //else if (AProjectileBase* DestroyedProjectile = Cast<AProjectileBase>(DestroyedActor))
    //{
    //    DestroyedProjectile = Cast<AProjectileAsteroid>(DestroyedActor);

    //    if (DestroyedProjectile)
    //    {
    //        if (--TargetAsteroids == 0)
    //        {
    //            HandleGameOver(true);
    //        }
    //    }

    //    //DestroyedProjectile->DestroyProjectile();
    //}
}

void AAsteroidsGameModeBase::HandleGameStart()
{
    TargetAsteroids = GetTargetAsteroidsCount();
    PlayerRocket = Cast<ARocketPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
    //RocketPlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    GameStart();

    /*if (RocketPlayerControllerRef)
    {
        RocketPlayerControllerRef->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(RocketPlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);

        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
    }*/
}

void AAsteroidsGameModeBase::HandleGameOver(bool PlayerWon)
{
    GameOver(PlayerWon);
}

int32 AAsteroidsGameModeBase::GetTargetAsteroidsCount()
{
    int32 TempCount = 0;
    TArray<AActor*> AsteroidActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProjectileAsteroid::StaticClass(), AsteroidActors);

    for (int i = 0; i < AsteroidActors.Num(); i++)
    {
        int TempScore = Cast<AProjectileAsteroid>(AsteroidActors[i])->GetScoreValue();

        if (TempScore == 100)
        {
            TempCount += 7;
        }
        else if (TempScore == 200)
        {
            TempCount += 3;
        }
        else if (TempScore == 300)
        {
            TempCount++;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Number of Asteroid Targets: %i"), TempCount);
    return TempCount;
}