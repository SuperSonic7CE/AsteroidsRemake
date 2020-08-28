// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidsGameModeBase.generated.h"

class ARocketPawn;
//class APlayerControllerBase;

UCLASS()
class ASTEROIDSREMAKE_API AAsteroidsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:

    ARocketPawn* PlayerRocket;
    int32 TargetAsteroids = 0;
    //APlayerControllerBase* RocketPlayerControllerRef;

    int32 GetTargetAsteroidsCount();
    void HandleGameStart();
    void HandleGameOver(bool PlayerWon);

public:

    void ActorDestroyed(AActor* DestroyedActor);

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
        int32 StartDelay = 3;

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent)
        void GameStart();
    UFUNCTION(BlueprintImplementableEvent)
        void GameOver(bool PlayerWon);
};
