// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FPlayerSetup
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APCharacter> CharacterClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;
};

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
	UPROPERTY(EditAnywhere)
	FPlayerSetup PlayerSetup;

public:
	UFUNCTION(BlueprintCallable)
	class APLevelManager *GetLevelManager();
	UFUNCTION(BlueprintCallable)
	class APDataManager *GetDataManager();

	UFUNCTION(BlueprintCallable)
	void SetPlayerClass(TSubclassOf<class APCharacter> CharacterClass);
	UFUNCTION(BlueprintCallable)
	void SetLevel(int Level);	
	UFUNCTION(BlueprintCallable)
	FPlayerSetup GetPlayerSetup();
};
