/*
Steven Esposito
8/29/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidsGameModeBase.generated.h"

class ARocketPawn;

UCLASS()
class ASTEROIDSREMAKE_API AAsteroidsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

private:

    AAsteroidsGameModeBase();

    ARocketPawn* PlayerRocket;
    int32 TargetAsteroids;
    int32 TotalScore;
    UAudioComponent* CurrentBackgroundAudio;

    int32 GetTargetAsteroidsCount();
    void HandleGameStart();
    void HandleGameOver(bool PlayerWon);
    void StopBackgroundAudio(float StopDelay);

    virtual void Tick(float DeltaSeconds) override;


public:

    void ActorDestroyed(AActor* DestroyedActor);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point Values")
        int32 BigAsteroidPoints;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point Values")
        int32 MediumAsteroidPoints;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point Values")
        int32 SmallAsteroidPoints;

    UFUNCTION()
        int32 GetBigAsteroidPoints();
    UFUNCTION()
        int32 GetMediumAsteroidPoints();
    UFUNCTION()
        int32 GetSmallAsteroidPoints();


protected:
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
        float ReviveDelay;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
        int32 ScoreValue;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
        int32 PlayerLives;

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent)
        void GameStart();
    UFUNCTION(BlueprintImplementableEvent)
        void GameOver(bool PlayerWon);
    UFUNCTION(BlueprintImplementableEvent)
        void SetScoreDisplay(int32 ScoreDisplayValue);
    UFUNCTION(BlueprintImplementableEvent)
        void SetLivesDisplay(int32 LivesDisplayValue);

    UPROPERTY(EditAnywhere, Category = "Effects")
        USoundBase* BackgroundAudio;
};
