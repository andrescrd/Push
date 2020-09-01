// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PGameMode.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	Won,
	Draw,
	Playing,
	GameOver,
	Unknow
};

/**
 * 
 */
UCLASS()
class PUSH_API APGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APGameMode();

private:
	EGameState CurrentGameState;
	TArray<class APCharacter *> AllCharacters;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void HandleGameState(EGameState NewState);
	bool CheckIsAnyPlayerAlive();	
	bool IsPlayerAlive();

public:
	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const;

	UFUNCTION(BlueprintCallable)
	void SetCurrentGameState(EGameState NewState);
};
