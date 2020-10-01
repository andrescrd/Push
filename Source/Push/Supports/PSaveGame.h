// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Push/Managers/PLevelManager.h"
#include "PSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PUSH_API UPSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FLevelStruct> Levels;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;
};
