// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "PLevelManager.generated.h"

UENUM(BlueprintType)
enum class ELevelState : uint8
{
	Locked,
	Unlocked
};

USTRUCT(BlueprintType)
struct FLevelStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELevelState State;

	FLevelStruct()
	{
		LevelName = TEXT("NONE");
		State = ELevelState::Locked;
	}
};

/**
 * 
 */
UCLASS(Blueprintable)
class PUSH_API APLevelManager : public AInfo
{
	GENERATED_BODY()

private:
	FName CleanLevelString(class UObject *context);

protected:
	UPROPERTY(VisibleAnywhere)
	FLevelStruct CurrentLevel;
	UPROPERTY(EditAnywhere)
	TArray<FLevelStruct> Levels;

public:
	UFUNCTION(BlueprintCallable)
	void LoadLevel(class UObject* context,FName LevelNameToLoad);
	UFUNCTION(BlueprintCallable)
	TArray<FLevelStruct> GetLevels();
	UFUNCTION(BlueprintCallable)
	FLevelStruct GetFirstLavel();
	UFUNCTION(BlueprintCallable)
	FLevelStruct GetNextLevel(class UObject* context);
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel(class UObject* context);
};
