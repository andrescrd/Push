// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUSH_API UPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;

protected:

	// Managers
	UPROPERTY(Transient)
	class APLevelManager *LevelManagerInstance;
	UPROPERTY(Transient)
	class APDataManager *DataManagerInstance;

	// Player Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APLevelManager> LevelManagerClass;

public:
	UFUNCTION(BlueprintCallable)
	class APLevelManager *GetLevelManager();
	UFUNCTION(BlueprintCallable)
	class APDataManager *GetDataManager();
};
