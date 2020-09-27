// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PGameMode.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	Preparing UMETA(DisplayName = "Preparing"),
	Playing UMETA(DisplayName = "Playing"),
	Won UMETA(DisplayName = "Won"),
	Draw UMETA(DisplayName = "Draw"),
	GameOver UMETA(DisplayName = "GameOver"),
	Unknow UMETA(DisplayName = "Unknow")
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
	FTimerHandle TimerHandle_InitGame;

	UPROPERTY(BlueprintReadOnly)
	int32 ActorsInSafeZone;
	UPROPERTY(BlueprintReadOnly)
	EGameState CurrentGameState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxNumberOfBots;

	TArray<class APCharacter *> AllCharacters;

	void HandleGameState(EGameState NewState);
	bool CheckIsAnyCharacterAlive();
	bool IsPlayerAlive();
	void SetCurrentGameState(EGameState NewState);
	void DisableAllCharacterMovement(TArray<class APCharacter *> Characters);
	void SpawnCharacterSelected();

	void InitPlayGame();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void AddActorToSafeZone(class AActor* OtherActor);
	void RemoveActorFromSafeZone(class AActor* OtherActor);
	
	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const;
	UFUNCTION(BlueprintCallable)
	int32 GetNumberOfCharacters();
	

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameStateChange(EGameState NewState);
};
