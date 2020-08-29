/*
Steven Esposito
8/29/2020
*/

#include "AsteroidsGameModeBase.h"
#include "AsteroidsRemake/Actors/ProjectileAsteroid.h"
#include "AsteroidsRemake/Pawns/RocketPawn.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

AAsteroidsGameModeBase::AAsteroidsGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAsteroidsGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    CurrentBackgroundAudio = UGameplayStatics::SpawnSound2D(this, BackgroundAudio);

    HandleGameStart();
}

void AAsteroidsGameModeBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Counts up to displaying TotalScore.
    if (ScoreValue < TotalScore)
    {
        ScoreValue += 5;
        SetScoreDisplay(ScoreValue);
    }
}

void AAsteroidsGameModeBase::ActorDestroyed(AActor* DestroyedActor)
{
    if (DestroyedActor == PlayerRocket)
    {
        PlayerRocket->DestroyPawn();

        // Instantly sets score when player is hit.
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
        if (!TargetAsteroids)
        {
            TargetAsteroids = GetTargetAsteroidsCount();
        }

        TotalScore += DestroyedAsteroid->GetScoreValue();
        DestroyedAsteroid->DestroyProjectile();

        if (--TargetAsteroids <= 0)
        {
            HandleGameOver(true);
        }
    }
}

void AAsteroidsGameModeBase::HandleGameStart()
{
    TotalScore = 0;
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

        /* Big Asteroid = 7 total asteroids to destroy 
           Medium Asteroid = 3 total asteroids to destroy 
           Small Asteroid = 1 asteroid to destroy
        */
        if (TempScore == BigAsteroidPoints)
        {
            TempCount += 7;
        }
        else if (TempScore == MediumAsteroidPoints)
        {
            TempCount += 3;
        }
        else if (TempScore == SmallAsteroidPoints)
        {
            TempCount++;
        }
    }

    //UE_LOG(LogTemp, Warning, TEXT("Number of Asteroid Targets: %i"), TempCount);
    return TempCount;
}

#pragma region Point Values

int32 AAsteroidsGameModeBase::GetBigAsteroidPoints()
{
    return BigAsteroidPoints;
}

int32 AAsteroidsGameModeBase::GetMediumAsteroidPoints()
{
    return MediumAsteroidPoints;
}

int32 AAsteroidsGameModeBase::GetSmallAsteroidPoints()
{
    return SmallAsteroidPoints;
}

#pragma endregion

void AAsteroidsGameModeBase::StopBackgroundAudio(float StopDelay)
{
    CurrentBackgroundAudio->StopDelayed(StopDelay);
}