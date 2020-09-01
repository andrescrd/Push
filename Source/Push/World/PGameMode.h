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

protected:
	UPROPERTY(BlueprintReadOnly)
	EGameState CurrentGameState;
	
	TArray<class APCharacter *> AllCharacters;


	void HandleGameState(EGameState NewState);
	bool CheckIsAnyPlayerAlive();	
	bool IsPlayerAlive();
	void SetCurrentGameState(EGameState NewState);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const;
	UFUNCTION(BlueprintCallable)
	int32 GetNumberOfPlayers();

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameStateChange(EGameState NewState);
	
};
