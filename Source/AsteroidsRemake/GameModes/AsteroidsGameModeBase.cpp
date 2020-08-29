/*
Steven Esposito
8/28/2020
*/

#include "AsteroidsGameModeBase.h"
#include "AsteroidsRemake/Actors/ProjectileAsteroid.h"
#include "AsteroidsRemake/Pawns/RocketPawn.h"
#include "Kismet/GameplayStatics.h"

void AAsteroidsGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    PrimaryActorTick.bCanEverTick = false;

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
}

void AAsteroidsGameModeBase::HandleGameStart()
{
    TargetAsteroids = GetTargetAsteroidsCount();
    PlayerRocket = Cast<ARocketPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

    GameStart();
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

        /* 100 points = Big Asteroid = 7 total asteroids to destroy 
           200 points = Medium Asteroid = 3 total asteroids to destroy 
           300 points = Small Asteroid = 1 asteroid to destroy
        */
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

    //UE_LOG(LogTemp, Warning, TEXT("Number of Asteroid Targets: %i"), TempCount);
    return TempCount;
}