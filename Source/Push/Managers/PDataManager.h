// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Push/Managers/PLevelManager.h"
#include "PDataManager.generated.h"

/**
 * 
 */
UCLASS()
class PUSH_API APDataManager : public AInfo
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
	class UPSaveGameManager* SaveGameInstance;


class UPSaveGameManager* GetSaveGameInstance();

public:
  void SaveLevels(TArray<FLevelStruct> LevelsToSave);
  TArray<FLevelStruct> GetLevels();
  void ClearData();
};
