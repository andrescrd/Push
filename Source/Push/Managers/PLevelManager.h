// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "PLevelManager.generated.h"



/**
 * 
 */
UCLASS(Blueprintable)
class PUSH_API APLevelManager : public AInfo
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	FName CurrentLevel;
	UPROPERTY(EditDefaultsOnly)
	TArray<FName> Levels;

public:
	UFUNCTION(BlueprintCallable)
	void LoadLevel(FName LevelNameToLoad);
	UFUNCTION(BlueprintCallable)
	TArray<FName> GetLevels();
	UFUNCTION(BlueprintCallable)
	FName GetFirstLavel();
	UFUNCTION(BlueprintCallable)
	FName GetNextLevel();
};
