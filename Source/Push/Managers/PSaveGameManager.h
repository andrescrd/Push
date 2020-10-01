// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Push/Managers/PLevelManager.h"
#include "PSaveGameManager.generated.h"

/**
 * 
 */
UCLASS()
class PUSH_API UPSaveGameManager : public USaveGame
{
	GENERATED_BODY()

public:
	UPSaveGameManager();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FLevelStruct> Levels;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;
};
