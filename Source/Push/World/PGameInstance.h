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

protected:
	class APLevelManager *LevelManager;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APLevelManager> LevelManagerClass;

public:
	UFUNCTION(BlueprintCallable)
	class APLevelManager *GetLevelManager() const;
};
