/*
Steven Esposito
8/28/2020
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

    ARocketPawn* PlayerRocket;
    int32 TargetAsteroids = 0;

    int32 GetTargetAsteroidsCount();
    void HandleGameStart();
    void HandleGameOver(bool PlayerWon);

    //virtual void Tick(float DeltaSeconds) override;

public:

    void ActorDestroyed(AActor* DestroyedActor);

protected:

    int ReviveDelay = 3;
    int32 TotalScore = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
        int32 ScoreValue = 0;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
        int32 PlayerLives = 3;

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
